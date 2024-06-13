import java.util.ArrayList;
import java.util.List;

public class Main {
    public static String stringSolution(String[][] messages, int width, int userWidth) {
        StringBuilder result = new StringBuilder();

        // Create top frame
        result.append("+" + "*".repeat(width - 2) + "+\n");

        // Render messages
        for (String[] message : messages) {
            String user = message[0];
            String text = message[1];
            List<String> lines = splitMessage(text, userWidth);

            for (int i = 0; i < lines.size(); i++) {
                String line = lines.get(i);
                String formattedLine = formatMessageLine(line, user, userWidth, width);
                result.append(formattedLine).append("\n");
            }
        }

        // Create bottom frame
        result.append("+" + "*".repeat(width - 2) + "+");

        return result.toString();
    }

    private static List<String> splitMessage(String text, int userWidth) {
        List<String> lines = new ArrayList<>();
        int index = 0;

        while (index < text.length()) {
            int endIndex = Math.min(index + userWidth, text.length());
            while (endIndex < text.length() && text.charAt(endIndex) != ' ') {
                endIndex--;
            }
            lines.add(text.substring(index, endIndex));
            index = endIndex + 1;
        }

        return lines;
    }

    private static String formatMessageLine(String line, String user, int userWidth, int width) {
        StringBuilder formattedLine = new StringBuilder("|");
        if (user.equals("1")) {
            formattedLine.append(line);
            formattedLine.append(" ".repeat(Math.max(0, userWidth - line.length())));
        } else if (user.equals("2")) {
            formattedLine.append(" ".repeat(Math.max(0, userWidth - line.length())));
            formattedLine.append(line);
        }
        formattedLine.append(" ".repeat(width - formattedLine.length() - 1));
        formattedLine.append("|");
        return formattedLine.toString();
    }

    public static void main(String[] args) {
        String[][] messages = {{"1", "Hello how r u"}, {"2", "good ty"}, {"2", "u"}, {"1", "me too bro"}};
        int width = 15;
        int userWidth = 5;

        String renderedWindow = stringSolution(messages, width, userWidth);
        System.out.println(renderedWindow);
    }
}
