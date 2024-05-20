import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

/**
 * Clasa Trenuri permite calcularea numarului maxim de orase distincte care se pot vizita
 * pornind de la un oras de plecare si ajungand la un oras destinatie
 */
public class Trenuri {

	/**
	 * Metoda principala care initiaza executia programului
	 *
	 * @param args 					 argumentele liniei de comanda (nu sunt folosite)
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public static void main(String[] args) throws FileNotFoundException {
		Trenuri trenuri = new Trenuri();
		trenuri.execute();
	}

	/**
	 * Citeste datele de intrare, calculeaza numarul maxim de orase distincte
	 * si scrie rezultatul in fisierul de iesire
	 *
	 * @throws FileNotFoundException daca fisierul de intrare nu este gasit
	 */
	public void execute() throws FileNotFoundException {
		Scanner scanner = new Scanner(new File("trenuri.in"));

		String startCity = scanner.next();
		String destinationCity = scanner.next();
		Map<String, List<String>> trainRoute = readTrainRoute(scanner);

		int maxDistinctCities = maxDistinctCities(trainRoute, startCity, destinationCity);

		writeResult(maxDistinctCities);

		scanner.close();
	}

	/**
	 * Citeste lista de curse din fisierul de intrare (graful)
	 *
	 * @param scanner scannerul utilizat pentru citirea datelor de intrare
	 * @return mapa care contine lista de curse
	 */
	private Map<String, List<String>> readTrainRoute(Scanner scanner) {
		int routes = scanner.nextInt();
		Map<String, List<String>> trainRoute = new HashMap<>();
		for (int i = 0; i < routes; i++) {
			String sourceCity = scanner.next();
			String destinationCity = scanner.next();
			trainRoute.computeIfAbsent(sourceCity, key -> new ArrayList<>()).add(destinationCity);
		}
		return trainRoute;
	}

	/**
	 * Scrie rezultatul in fisierul de iesire
	 *
	 * @param result 				 rezultatul de scris in fisier
	 * @throws FileNotFoundException daca fisierul de iesire nu poate fi creat
	 */
	private void writeResult(int result) throws FileNotFoundException {
		try (PrintWriter printWriter = new PrintWriter("trenuri.out")) {
			printWriter.println(result);
		}
	}

	/**
	 * Calculeaza numarul maxim de orase distincte utilizand o cautare in adancime (DFS)
	 *
	 * @param trainRoute       reteaua de curse
	 * @param currentCity      orasul curent
	 * @param destinationCity  orasul destinatie
	 * @return numarul maxim de orase distincte care pot fi vizitate
	 */
	private int maxDistinctCities(
			Map<String, List<String>> trainRoute,
			String currentCity,
			String destinationCity
	) {
		return dfsHelper(trainRoute, currentCity, destinationCity, new HashMap<>());
	}

	/**
	 * Metoda auxiliara pentru cautarea in adancime care calculeaza numarul maxim de orase distincte
	 *
	 * @param trainRoute       reteaua de curse
	 * @param currentCity      orasul curent
	 * @param destinationCity  orasul destinatie
	 * @param maxCitiesMap     mapa care memoreaza numarul maxim de orase pentru fiecare oras
	 * @return numarul maxim de orase distincte care pot fi vizitate
	 */
	private int dfsHelper(
			Map<String, List<String>> trainRoute,
			String currentCity,
			String destinationCity,
			Map<String, Integer> maxCitiesMap
	) {
		if (currentCity.equals(destinationCity)) {
			return 1;
		}
		if (maxCitiesMap.containsKey(currentCity)) {
			return maxCitiesMap.get(currentCity);
		}

		int maxCities = 0;

		if (trainRoute.containsKey(currentCity)) {
			for (String neigh : trainRoute.get(currentCity)) {
				int citiesCount = dfsHelper(trainRoute, neigh, destinationCity, maxCitiesMap);
				maxCities = Math.max(maxCities, citiesCount);
			}
		}

		if (maxCities > 0) {
			maxCitiesMap.put(currentCity, maxCities + 1);
		} else {
			maxCitiesMap.put(currentCity, 0);
		}

		return maxCitiesMap.get(currentCity);
	}
}