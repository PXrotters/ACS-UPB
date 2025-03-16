import java.io.*;
import java.util.*;
import java.util.stream.Collectors;

/**
 * RegexGenerator genereaza o expresie regulata ce accepta cuvintele
 * dintr-un limbaj Accept si respinge cuvintele din limbajul Fail.
 */
public class RegexGenerator {

    /**
     * Citirea datelor din fisierul de intrare.
     *
     * @param reader BufferedReader pentru citirea fisierului de intrare.
     * @param acceptWords Lista care va contine cuvintele din limbajul Accept.
     * @param failWords Lista care va contine cuvintele din limbajul Fail.
     * @param lenString Array care stocheaza lungimea cuvintelor din limbaje.
     * @throws IOException Daca apare o eroare la citirea fisierului.
     */
    public static void readInput(BufferedReader reader, List<String> acceptWords, List<String> failWords, int[] lenString) throws IOException {
        // Prima linie contine numarul de cuvinte Accept si Fail, si lungimea acestora
        String[] firstLine = reader.readLine().split(" ");
        int cntAccept = Integer.parseInt(firstLine[0]);
        int cntFail = Integer.parseInt(firstLine[1]);
        lenString[0] = Integer.parseInt(firstLine[2]);

        // Citirea cuvintelor din limbajul Accept
        for (int i = 0; i < cntAccept; i++) {
            acceptWords.add(reader.readLine());
        }

        // Citirea cuvintelor din limbajul Fail
        for (int i = 0; i < cntFail; i++) {
            failWords.add(reader.readLine());
        }
    }

    /**
     * Grupeaza cuvintele dupa prefixe de lungime specifica.
     *
     * @param words Lista de cuvinte care trebuie grupate.
     * @param prefixLength Lungimea prefixului folosit pentru grupare.
     * @return Un map care asociaza fiecare prefix cu lista de cuvinte care au acel prefix.
     */
    public static Map<String, List<String>> groupByPrefix(List<String> words, int prefixLength) {
        return words.stream().collect(Collectors.groupingBy(word -> word.substring(0, Math.min(prefixLength, word.length()))));
    }

    /**
     * Construieste un regex pentru un grup de cuvinte care au acelasi prefix.
     *
     * @param prefix Prefixul comun al cuvintelor din grup.
     * @param group Lista de cuvinte care apartin grupului.
     * @return Un regex care accepta toate cuvintele din grup.
     */
    public static String buildGroupRegex(String prefix, List<String> group) {
        if (group.size() == 1) {
            return group.get(0);  // Caz simplu: un singur cuvant
        }

        StringBuilder regex = new StringBuilder();
        regex.append(prefix).append("(");
        for (int i = 0; i < group.size(); i++) {
            if (i > 0) regex.append("|");
            regex.append(group.get(i).substring(prefix.length()));
        }
        regex.append(")");
        return regex.toString();
    }

    /**
     * Concateneaza toate grupurile de cuvinte intr-un regex complet.
     *
     * @param grouped Map cu prefixe si grupurile lor de cuvinte asociate.
     * @return Regex complet care accepta toate cuvintele din limbajul Accept.
     */
    public static String combineGroups(Map<String, List<String>> grouped) {
        StringBuilder regex = new StringBuilder();
        regex.append("(");

        boolean firstGroup = true;
        for (Map.Entry<String, List<String>> entry : grouped.entrySet()) {
            if (!firstGroup) regex.append("|");
            firstGroup = false;
            regex.append(buildGroupRegex(entry.getKey(), entry.getValue()));
        }

        regex.append(")");
        return regex.toString();
    }

    /**
     * Construieste regex-ul final din lista de cuvinte acceptate.
     *
     * @param words Lista de cuvinte acceptate.
     * @param lenString Lungimea fiecarui cuvant.
     * @return Regex complet.
     */
    public static String groupWords(List<String> words, int lenString, int prefixLength) {
        Map<String, List<String>> grouped = groupByPrefix(words, prefixLength);
        return combineGroups(grouped);
    }

    /**
     * Genereaza expresia regulata finala.
     *
     * @param acceptWords Lista de cuvinte acceptate.
     * @param failSet Set de cuvinte respinse.
     * @param lenString Lungimea fiecarui cuvant.
     * @param prefixLength Lungimea prefixului utilizat pentru gruparea cuvintelor.
     * @return Regex final care indeplineste cerintele.
     */
    public static String generateRegex(List<String> acceptWords, Set<String> failSet, int lenString, int prefixLength) {
        // Filtram cuvintele care nu se afla in Fail
        List<String> filteredWords = acceptWords.stream().filter(word -> !failSet.contains(word)).collect(Collectors.toList());
        return "regex\n" + groupWords(filteredWords, lenString, prefixLength);  // Grupeaza dupa primele prefixLength litere
    }

    /**
     * Scrie rezultatul in fisierul de iesire.
     *
     * @param writer BufferedWriter pentru scrierea fisierului de iesire.
     * @param regex Regex-ul generat.
     * @throws IOException Daca apare o eroare la scrierea fisierului.
     */
    public static void writeOutput(BufferedWriter writer, String regex) throws IOException {
        writer.write(regex);
        writer.newLine();
    }

    /**
     * Determina lungimea optima a prefixului pentru a genera un regex cat mai scurt.
     *
     * @param acceptWords Lista de cuvinte acceptate.
     * @param lenString Lungimea fiecarui cuvant.
     * @return Lungimea optima a prefixului, care genereaza regex-ul cel mai scurt.
     */
    public static int findOptimalPrefixLength(List<String> acceptWords, int lenString) {
        int bestPrefixLength = 1;
        int minRegexLength = Integer.MAX_VALUE;

        for (int prefixLength = 1; prefixLength <= 10; prefixLength++) {
            String regex = groupWords(acceptWords, lenString, prefixLength);
            if (regex.length() < minRegexLength) {
                minRegexLength = regex.length();
                bestPrefixLength = prefixLength;
            }
        }

        return bestPrefixLength;
    }


    /**
     * Entry point-ul programului.
     */
    public static void main(String[] args) {
        try (BufferedReader reader = new BufferedReader(new FileReader("input.txt"));
             BufferedWriter writer = new BufferedWriter(new FileWriter("output.txt"))) {

            List<String> acceptWords = new ArrayList<>();
            List<String> failWords = new ArrayList<>();
            int[] lenString = new int[1];

            // Citim datele de intrare
            readInput(reader, acceptWords, failWords, lenString);

            // Cream un set pentru cuvintele din Fail
            Set<String> failSet = new HashSet<>(failWords);

            // Generam lungimea optima a prefixului
            int optimalPrefixLength = findOptimalPrefixLength(acceptWords, lenString[0]);

            // Generam expresia regulata
            String regex = generateRegex(acceptWords, failSet, lenString[0], optimalPrefixLength);

            // Scriem rezultatul in fisierul de iesire
            writeOutput(writer, regex);

        } catch (IOException e) {
            e.printStackTrace();
        }
    }
}
