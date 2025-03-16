#include "checker_utils.h"

const int TIME_LIMIT_SECONDS = 60;
const int MAX_TIME_LIMIT_SECONDS = 400;
const char REGEX_REGEX_STR[]="([a-z]|\\(|\\)|\\*|\\+|\\.|\\|)*";
const std::regex REGEX_REGEX(REGEX_REGEX_STR);

///daca raspunsul participantului este acceptat, intorc (tip raspuns participant: "dfa" sau "regex", marimea raspunsului lui - nr stari automat sau lg regex).
std::optional<std::pair<std::string, int>> evaluateOutput(std::ifstream &fin, std::ifstream &participant) {
#define BYE(bye_str) { std::cout << bye_str << '\n'; return std::nullopt; }
#define CHECK_READ_PAIR(x) if (!(x).second.empty()) BYE((x).second)

    std::string answerType; participant >> answerType;

    int partLen = 0;
    if (answerType == "dfa") {
        DFA dfa;
        auto res = dfa.readDFA(participant);
        if(res)
            BYE(res.value())
        
        auto cnt_accept = readInt(fin, 1, 1000, "cnt_accept"); CHECK_READ_PAIR(cnt_accept);
        auto cnt_fail = readInt(fin, 1, 1000, "cnt_fail"); CHECK_READ_PAIR(cnt_fail);
        auto len_string = readInt(fin, 1, 1000, "len_string"); CHECK_READ_PAIR(len_string);

        std::string s; 
        for (int i = 0; i < cnt_accept.first + cnt_fail.first; i++) {
            fin >> s;
            if ((int)s.size() != len_string.first) BYE("Input string length different from len_string.")

            if (i < cnt_accept.first) {
                if (!dfa.accepts(s)) BYE("The string " + s + " was supposed to be accepted, but it isn't.")
            } else {
                if (dfa.accepts(s)) BYE("The string " + s + " wasn't supposed to be accepted, but it was.")
            }
        }

        partLen = dfa.size();

    } else if (answerType == "regex") {
        std::string part_str; participant >> part_str;

        if(!std::regex_match(part_str, REGEX_REGEX)) BYE("Regex is invalid.")

        std::regex part_regex(part_str);

        auto cnt_accept = readInt(fin, 1, 1000, "cnt_accept"); CHECK_READ_PAIR(cnt_accept);
        auto cnt_fail = readInt(fin, 1, 1000, "cnt_fail"); CHECK_READ_PAIR(cnt_fail);
        auto len_string = readInt(fin, 1, 1000, "len_string"); CHECK_READ_PAIR(len_string);

        std::string s; 
        for (int i = 0; i < cnt_accept.first + cnt_fail.first; i++) {
            fin >> s;
            if ((int)s.size() != len_string.first) BYE("Input string length different from len_string.")

            if (i < cnt_accept.first) {
                if (!std::regex_match(s, part_regex)) BYE("The string " + s + " was supposed to regex match, but it didn't.")
            } else {
                if (std::regex_match(s, part_regex)) BYE("The string " + s + " wasn't supposed to regex match, but it did.")
            }
        }

        partLen = part_str.size();
    } else {
        BYE("Unknown answer type: " + answerType + ", expecting either dfa or regex.")
    }

#undef CHECK_READ_PAIR
#undef BYE

    return std::optional<std::pair<std::string, int>>(std::make_pair(answerType, partLen));
}

int main(int argc, char **argv) {
    ///maresc dimensiunea stivei la 256MB.
    struct rlimit rl;
    const rlim_t kStackSize = 256L * 1024L * 1024L;
    assert(!getrlimit(RLIMIT_STACK, &rl));
    rl.rlim_cur = kStackSize;
    assert(!setrlimit(RLIMIT_STACK, &rl));

    if (argc != 3) {
        std::cerr << "usage: ./checker_main <..locatie checker_info.txt..> <..director makefile cod de testat..>" << '\n';
        std::cerr << "ex ./checker_main checker_info.txt ../src/" << '\n';
        return 0;
    }

    std::string implLoc(argv[2]);
    assert(implLoc.back() == '/');

    system((std::string("make --no-print-directory -C ") + implLoc + " build").c_str()); ///compilez codul participantului.

    std::ifstream checkerInfo(argv[1]);
    assert(checkerInfo.is_open());

    double maxTimeLeft = MAX_TIME_LIMIT_SECONDS;
    double scor = 0;
    std::string checkerLine;

    std::cout << std::fixed << std::setprecision(4);
    while (std::getline(checkerInfo, checkerLine)) {
        if (!checkerLine.empty() && checkerLine[0] != '#') {
            boost::tokenizer<boost::char_separator<char>> tokenizer(checkerLine, boost::char_separator<char>(" \n"));

            std::vector<std::string> tokens;
            for (const std::string &tok: tokenizer) {
                tokens.push_back(tok);
            }

            std::string &testInput = tokens[0], &testOutputDfa = tokens[1], &testOutputRegex = tokens[2];
            int scorNow = atoi(tokens[3].c_str());

            ///copiez inputul testului in input.txt.
            system((std::string("cp ") + testInput + " " + implLoc + "input.txt").c_str());

            std::cout << "running test " << testInput << ":\n";

            ///rulez codul participantului.
            int timeLimitParticipant = std::max(1, std::min(TIME_LIMIT_SECONDS, (int)maxTimeLeft));

            auto start = std::chrono::steady_clock::now();
            int retVal = system((std::string("timeout ") +
                                std::to_string(timeLimitParticipant) +
                                std::string(" make --no-print-directory -C ") + implLoc + " run").c_str());

            double timePassed = std::chrono::duration_cast<std::chrono::microseconds>(std::chrono::steady_clock::now() - start).count() / 1e6;
            maxTimeLeft -= timePassed;

            if (retVal == 124) {
                std::cout << "(" << testInput << ") time limit of " << TIME_LIMIT_SECONDS << " s exceeded.\n";
            } else if (retVal != 0) {
                std::cout << "(" << testInput << ") participant's process ended unexpectedly with retVal = " << retVal << '\n';
                std::cout << "(" << testInput << ") process ran for: " << timePassed << " s.\n";
            } else {
                std::cout << "(" << testInput << ") process ran for: " << timePassed << " s.\n";

                std::ifstream fin(testInput);
                std::ifstream fout_dfa(testOutputDfa);
                std::ifstream fout_regex(testOutputRegex);
                std::ifstream participant(implLoc + "output.txt");

                std::optional<std::pair<std::string, int>> evalAns = evaluateOutput(fin, participant);
                double testScore = 0;

                if (evalAns.has_value()) {
                    std::string answerType; ///"dfa" sau "regex".
                    int partLen;

                    std::tie(answerType, partLen) = evalAns.value();

                    int refLen = 0;
                    if (answerType == "regex") {
                        std::string outType, judgeRegex; fout_regex >> outType >> judgeRegex;
                        refLen = judgeRegex.size();
                    } else {
                        std::string outType; fout_dfa >> outType >> refLen;
                    }

                    double raport = 2 * (double)refLen / (refLen + partLen);
                    testScore = scorNow * raport;

                    std::cout << "test multiplier = " << raport << '\n';
                }

                std::cout << "(" << testInput << ") current test score: " << testScore << '\n' << std::flush;
                scor += testScore;
            }

            ///sterg input.txt, output.txt
            system((std::string("rm ") + implLoc + "input.txt").c_str());
            system((std::string("rm ") + implLoc + "output.txt").c_str());

            std::cout << "time left till timeout: " << maxTimeLeft << '\n' << std::flush;
            std::cout << "partial score: " << std::min(scor, 150.0) << "/150\n" << std::flush;
        }
    }

    ///sterg executabilul participantului.
    system((std::string("make --no-print-directory -C ") + implLoc + " clean").c_str());

    std::cout << "Total: " << std::min(int(ceil(scor)), 150) << "/150\n" << std::flush;

    return 0;
}
