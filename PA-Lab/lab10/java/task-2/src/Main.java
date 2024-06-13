import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.PriorityQueue;

public class Main {
    static class Task {
        public static final String INPUT_FILE = "in";
        public static final String OUTPUT_FILE = "out";

        // numarul maxim de noduri
        public static final int NMAX = 1005;

        // valoare mai mare decat orice distanta din graf
        public static final int INF = (int) 1e9;

        // n = numar de noduri, m = numar de muchii
        int n, m;

        // structura folosita pentru a stoca distanta, vectorul de parinti
        // si daca s-a intalnit un ciclu de cost negativ folosind algoritmul
        // Bellman-Ford
        public class BellmanFordResult {
            List<Integer> d;
            List<Integer> p;
            boolean hasCycle;

            BellmanFordResult(boolean _hasCycle, List<Integer> _d, List<Integer> _p) {
                hasCycle = _hasCycle;
                d = _d;
                p = _p;
            }
        };

        // structura folosita pentru a stoca distanta, cat si vectorul de parinti
        // folosind algoritmul Dijkstra
        public class DijkstraResult {
            List<Integer> d;
            List<Integer> p;

            DijkstraResult(List<Integer> _d, List<Integer> _p) {
                d = _d;
                p = _p;
            }
        };

        // structura folosita pentru a stoca matricea de distante, matricea
        // de parinti si daca s-a intalnit un ciclu de cost negativ
        // folosind algoritmul lui Johnson.
        public class JohnsonResult {
            int d[][];
            int p[][];
            boolean hasCycle;

            JohnsonResult(boolean _hasCycle, int _d[][], int _p[][]) {
                hasCycle = _hasCycle;
                d = _d;
                p = _p;
            }
        };

        public class Pair implements Comparable<Pair> {
            public int destination;
            public int cost;

            Pair(int _destination, int _cost) {
                destination = _destination;
                cost = _cost;
            }

            public int compareTo(Pair rhs) {
                return Integer.compare(cost, rhs.cost);
            }
        }

        public class Edge {
            int node;
            int neigh;
            int w;

            Edge(int _node, int _neigh, int _w) {
                node = _node;
                neigh = _neigh;
                w = _w;
            }
        };

        // adj[node] = lista de adiacenta a nodului node
        // perechea (neigh, w) semnifica arc de la node la neigh de cost w
        @SuppressWarnings("unchecked")
        ArrayList<Pair> adj[] = new ArrayList[NMAX];

        public void solve() {
            readInput();
            writeOutput(getResult());
        }

        private void readInput() {
            try {
                Scanner sc = new Scanner(new BufferedReader(new FileReader(
                        INPUT_FILE)));
                n = sc.nextInt();
                m = sc.nextInt();

                for (int i = 1; i <= n; i++)
                    adj[i] = new ArrayList<>();
                for (int i = 1; i <= m; i++) {
                    int x, y, w;
                    x = sc.nextInt();
                    y = sc.nextInt();
                    w = sc.nextInt();
                    adj[x].add(new Pair(y, w));
                }
                sc.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private void writeOutput(JohnsonResult result) {
            try {
                BufferedWriter bw = new BufferedWriter(new FileWriter(
                        OUTPUT_FILE));
                StringBuilder sb = new StringBuilder();
                if (result.hasCycle) {
                    sb.append("Ciclu negativ!\n");
                } else {
                    for (int x = 1; x <= n; x++) {
                        for (int y = 1; y <= n; y++) {
                            sb.append(result.d[x][y]).append(' ');
                        }
                        sb.append('\n');
                    }
                }
                bw.write(sb.toString());
                bw.close();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
        }

        private JohnsonResult getResult() {
            // Step 1: Add a dummy node and connect it to all other nodes with zero-weight edges
            int dummyNode = n + 1;
            ArrayList<Edge> edges = new ArrayList<>();
            for (int i = 1; i <= n; i++) {
                edges.add(new Edge(dummyNode, i, 0));
            }

            // Step 2: Run Bellman-Ford algorithm from the dummy node
            BellmanFordResult bellmanResult = bellman(dummyNode, n + 1, edges);
            if (bellmanResult.hasCycle) {
                return new JohnsonResult(true, new int[n + 1][n + 1], new int[n + 1][n + 1]);
            }

            // Step 3: Re-weight the edges
            List<Integer> distances = bellmanResult.d;
            int[] h = new int[distances.size()];
            for (int i = 0; i < distances.size(); i++) {
                h[i] = distances.get(i);
            }
            for (Edge edge : edges) {
                edge.w += h[edge.node] - h[edge.neigh];
            }

            // Step 4: Run Dijkstra's algorithm from each node
            int[][] d = new int[n + 1][n + 1];
            int[][] p = new int[n + 1][n + 1];
            for (int u = 1; u <= n; u++) {
                DijkstraResult dijkstraResult = dijkstra(u, n, adj);
                List<Integer> distances1 = dijkstraResult.d;
                List<Integer> parents = dijkstraResult.p;
                for (int v = 1; v <= n; v++) {
                    // Re-weight the distances
                    d[u][v] = distances1.get(v) + h[v] - h[u];
                    // Revert the re-weighting for the parent nodes
                    if (parents.get(v) != 0) {
                        p[u][v] = parents.get(v);
                        p[u][v] = p[u][v] == dummyNode ? 0 : p[u][v];
                    }
                }
            }

            // Step 5: Revert the re-weighting of distances
            for (int u = 1; u <= n; u++) {
                for (int v = 1; v <= n; v++) {
                    if (d[u][v] != 0) {
                        d[u][v] += h[v] - h[u];
                    }
                }
            }

            return new JohnsonResult(false, d, p);
        }


        private DijkstraResult dijkstra(int source, int nodes, ArrayList<Pair> adj[]) {
            List<Integer> d = new ArrayList<>();
            List<Integer> p = new ArrayList<>();

            // Initializam distantele la infinit
            for (int node = 0; node <= nodes; node++) {
                d.add(INF);
                p.add(0);
            }

            // Folosim un priority queue de Pair, desi elementele noastre nu sunt tocmai
            // muchii.
            // Vom folosi field-ul de cost ca si distanta pana la nodul respectiv.
            // Observati ca am modificat clasa Pair ca sa implementeze interfata Comparable.
            PriorityQueue<Pair> pq = new PriorityQueue<>();

            // Inseram nodul de plecare in pq si ii setam distanta la 0.
            d.set(source, 0);
            pq.add(new Pair(source, 0));

            // Cat timp inca avem noduri de procesat
            while (!pq.isEmpty()) {
                // Scoatem head-ul cozii
                int cost = pq.peek().cost;
                int node = pq.poll().destination;

                // In cazul in care un nod e introdus in coada cu mai multe distante (pentru ca
                // distanta pana la el se imbunatateste in timp), vrem sa procesam doar
                // versiunea sa cu distanta minima. Astfel, dam discard la intrarile din coada
                // care nu au distanta optima.
                if (cost > d.get(node)) {
                    continue;
                }

                // Ii parcurgem toti vecinii.
                for (Pair e : adj[node]) {
                    int neigh = e.destination;
                    int w = e.cost;

                    // Se imbunatateste distanta?
                    if (d.get(node) + w < d.get(neigh)) {
                        // Actualizam distanta si parintele.
                        d.set(neigh, d.get(node) + w);
                        p.set(neigh, node);
                        pq.add(new Pair(neigh, d.get(neigh)));
                    }
                }
            }

            // Toate nodurile ce au distanta INF nu pot fi atinse din sursa, asa ca setam
            // distantele
            // pe -1.
            for (int i = 1; i <= nodes; i++)
                if (d.get(i) == INF)
                    d.set(i, -1);

            return new DijkstraResult(d, p);
        }

        private BellmanFordResult bellman(int source, int nodes, List<Edge> edges) {
            // Initializam distantele catre toate nodurile cu infinit

            List<Integer> d = new ArrayList<>();
            List<Integer> p = new ArrayList<>();

            // Initializam distantele la infinit
            for (int node = 0; node <= nodes; node++) {
                d.add(INF);
                p.add(0);
            }

            // Setez sursa la distanta 0.
            d.set(source, 0);

            // Fac N - 1 relaxari.
            for (int i = 1; i <= nodes - 1; i++) {
                // Parcurg toate muchiile:
                for (Edge edge : edges) {
                    int node = edge.node;
                    int neigh = edge.neigh;
                    int w = edge.w;
                    // Se imbunatateste distanta?
                    if (d.get(node) + w < d.get(neigh)) {
                        // Actualizam distanta si parintele.
                        d.set(neigh, d.get(node) + w);
                        p.set(neigh, node);
                    }
                }
            }

            // Verific daca mai poate fi updatata distanta.
            for (Edge edge : edges) {
                int node = edge.node;
                int neigh = edge.neigh;
                int w = edge.w;
                // Se imbunatateste distanta?
                if (d.get(node) + w < d.get(neigh)) {
                    // Am gasit un ciclu de cost negativ.
                    return new BellmanFordResult(true, new ArrayList<>(), new ArrayList<>());
                }
            }

            // Toate nodurile catre care distanta este inca INF nu pot fi atinse din
            // nodul source, deci le setam pe -1.
            for (int node = 1; node <= nodes; node++) {
                if (d.get(node) == INF) {
                    d.set(node, -1);
                }
            }

            return new BellmanFordResult(false, d, p);
        }

    }

    public static void main(String[] args) {
        new Task().solve();
    }
}
