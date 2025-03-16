#include "checker_utils.h"

std::pair<int, std::string> readInt(std::ifstream &in, int l, int r, const std::string& name) {
    int x; in >> x;
    if (in.fail()) {
        return std::make_pair(0, "Can't read any further, blocked at " + name + ".");
    }

    if (x < l || x > r) {
        return std::make_pair(0, name + " is not in the interval [" + std::to_string(l) + ", " + std::to_string(r) + "].");
    }

    return std::make_pair(x, "");
}

double sigmoidStretch2x(int x) {
    if (x == 0) return 1.0;
    double y = x * 0.00390625;
    if (y > 10) return 2.0;
    if (y < -10) return 0.0;
    double ex = exp(y);
    return 2.0 * ex / (1 + ex);
}

DFA::DFA() {
}

DFA::~DFA() {
    delete[] mat;
}

std::optional<std::string> DFA::readDFA(std::ifstream &in) {
    unsigned int f, i, j;
    in >> n >> f >> start;

    if (in.fail())
        return "Reading from input failed";

    while(f--) {
        unsigned int state;
        in >> state;
        if (state >= n)
            return "Invalid final state";

        fin.insert(state);
    }

    mat = new unsigned int[n][26];
    for(i = 0; i < n; i++)
        for(j = 0; j < 26; j++){
            in >> mat[i][j];
            if (mat[i][j] >= n)
                return "Invalid destination state";
        }

    if (in.fail())
        return "Reading from input failed";

    return {};
}

bool DFA::accepts(std::string word) {
    unsigned int current_state = start;
    for (char it : word){
        current_state = mat[current_state][it-'a'];
    }

    return fin.find(current_state) != fin.end();
}

unsigned int DFA::size() {
    return n;
}
