import java.util.*;

public class Main {
    public static void main(String[] args) {
        Scanner scanner = new Scanner(System.in);
        int t = scanner.nextInt();
        scanner.nextLine();

        while (t-- > 0) {
            String[] input = scanner.nextLine().split(" ");
            int n = Integer.parseInt(input[0]);
            Set<Integer> skillLevels = new HashSet<>();

            for (int i = 1; i <= n; i++) {
                int skillLevel = Integer.parseInt(input[i]);
                skillLevels.add(skillLevel);
            }

            int minTeamSize = calculateMinTeamSize(skillLevels);
            System.out.println(minTeamSize);
        }

        scanner.close();
    }

    private static int calculateMinTeamSize(Set<Integer> skillLevels) {
        List<Integer> skillLevelsList = new ArrayList<>(skillLevels);
        Collections.sort(skillLevelsList);

        int minTeamSize = skillLevelsList.size();
        int prevSkillLevel = skillLevelsList.get(0);

        for (int i = 1; i < skillLevelsList.size(); i++) {
            int currentSkillLevel = skillLevelsList.get(i);

            if (currentSkillLevel != prevSkillLevel + 1) {
                minTeamSize = Math.min(minTeamSize, i);
            }

            prevSkillLevel = currentSkillLevel;
        }

        return minTeamSize;
    }

}
