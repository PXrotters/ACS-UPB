# Lemnaru Mihai-Daniel
## 322 CD

---

## 🧮 PROBLEMA 1: NUMARARE

### 📜  DESCRIERE IMPLEMENTARE
- **`main`:** Metoda principala care executa programul.

- **`execute`:** Metoda care ne ajuta sa citim datele de intrare din fisier, si sa afisam rezultatul final in fisierul de iesire.

- **`readGraph`:** Metoda care ne ajuta sa construim un graf de dimensiune N si M.

- **`writeResult`:** Metoda care ne ajuta sa scriem rezultatul obtinut in fisierul de iesire.

- **`topologicalSort`:** Metoda care ne ajuta sa realizam sortarea topologica a unui graf orientat cu ajutorul algoritmului lui Kahn. Initial am initializat o lista topSort care va stoca rezultatul sortarii topologice. Am calculat gradul intern al fiecarui nod folosind metoda "calculateInDegrees" si am initializat o coada pentru a stoca nodurile cu grad intern 0. Pe urma, parcurg coada si pentru fiecare nod il adaugam in lista de topSort si reducem gradul intern al fiecarui vecin, iar daca vreunul devine 0 il adaugam in coada. La final, verificam daca sortarea topoligica a fost realizata cu succes(graful nu contine cicluri).

- **`calculateInDegrees`:** Metoda care cacluleaza gradele interne pentru fiecare nod dintr-un graf.

- **`countElementaryChains`:** Metoda care calculeaza numarul de lanturi elementare pentru fiecare nod dintr-un graf, folosind sortarea topologica a acestuia. Am initializat o lista chainsCount care va stoca numarul de lanturi elementare pentru fiecare nod din graf. Am setat un lant elementar pentru primul nod, adica nodul 1, la 1. Pe urma, pentru fiecare nod din sortarea topologica am iterat prin toti vecinii acestui nod si am actualizat numarul de lanturi elementare pentru fiecare vecin(v) in functie de numarul de lanturi elementare ale nodului curent(u). Numarul de lanturi elementare pentru nodul v devine suma numarului lanturilor elementare ale nodului u si ale lui v.

- **`commonElementaryChainsGraph`:** Metoda care construieste un graf ce reprezinta lanturile elementare comune dintre 2 grafuri. Am initializat graful comun si am adaugat listele de adiacenta corespunzatoare fiecarui nod. Pentru fiecare nod si vecin din graful comun se verifica daca exista o muchie intre acelasi nod din ambele grafuri. Daca da, se adauga vecinul in graful comun.

### ⏳ COMPLEXITATE
- **`readGraph`:** `O(N + M)`
- **`writeResult`:** `O(1)`
- **`calculateInDegrees`:** `O(1)`
- **`countElementaryChains`:** `O(N + M)`
- **`commonElementaryChainsGraph`:** `O(N * M)`
- **`execute`:** `O(N * M)`
- **`main`:** `O(N * M)`
- **COMPLEXITATE TOTALA:** `O(N * M)`

---

## 🚄 PROBLEMA 2: TRENURI

### 📜 DESCRIERE IMPLEMENTARE:
- **`main`:** Metoda principala care executa programul.

- **`execute`:** Metoda care ne ajuta sa citim datele de intrare din fisier, si sa afisam rezultatul final in fisierul de iesire.

- **`readGraph`:** Metoda care ne ajuta sa construim un graf pe baza oraselor din fisierul de input.

- **`writeResult`:** Metoda care ne ajuta sa scriem rezultatul obtinut in fisierul de iesire.

- **`maxDistinctCities`:** Metoda care ne ajuta sa calculam numarul maxim de orase distincte care se pot vizita apeland functia "dfsHelper".

- **`dfsHelper`:** Metoda care ne ajuta sa calculam numarul maxim de orase distincte care se pot vizita intre orasul de plecare si orasul destinatie, utilizand DFS. Initial am verificat daca orasul curent este deja orasul destinatie, caz in care ne oprim. Altfel, verificam daca numarul maxim de orase pentru orasul curent a fost deja calculat si stocat. Pe urma, pentru fiecare oras vecin al orasului curent, exploram recursiv numarul maxim de orase care se pot vizita pornind de la vecinul respectiv. Apelam recursiv functia "dfsHelper" pentru a calcula numarul maxim de orase de la vecinul curent catre destinatie si actualizam numarul maxim de orase, alegand maximul dintre valoarea anterioara si numarul de orase calculat de la vecinul curent. La final, actualizam mapa ce contine numarul maxim de orase care se pot vizita pentru orasul curent. Daca exista cel putin un oras vecin catre destinatie, adaugam 1 la numarul maxim, altfel il facem 0.

### ⏳ COMPLEXITATE
- **`readTrainRoute`:** `O(M)`
- **`writeResult`:** `O(1)`
- **`dfsHelper`:** `O(N)`
- **`maxDistinctCities`:** `O(N)`
- **`execute`:** `O(N)`
- **`main`:** `O(N)`
- **COMPLEXITATE TOTALA:** `O(N)`

---

## 🚧 PROBLEMA 3 : DRUMURI

### 📜 DESCRIERE IMPLEMENTARE:
- **`main`:** Metoda principala care executa programul.

- **`execute`:** Metoda care ne ajuta sa citim datele de intrare din fisier, si sa afisam rezultatul final in fisierul de iesire.

- **`readEdges`:** Metoda care ne ajuta sa construim graful si graful transpus pe baza datelor din fisierul de input.

- **`writeResult`:** Metoda care ne ajuta sa scriem rezultatul obtinut in fisierul de iesire.

- **`dijkstra`:** Metoda care ne ajuta sa calculam distantele minime de la un nod de pornire dat la toate celelalte noduri dintr-un graf orientat si ponderat, folosind algoritmul lui Dijkstra. Initial am creat o coada de prioritati si un array initializat intai cu inf care marcheaza faptul toate distantele sunt momentan infinite. Se seteaza distanta de la nodul de start la 0 si acesta se adauga in coada. Pe urma pentru fiecare nod din coada se verifica toate muchiile sale adiacente. Pentru fiecare muchie se actualizeaza noua distanta posibila, iar daca aceasta este mai mica decat distanta cunoscuta se adauga nodul respectiv in coada de prioritati. La final, dupa ce toate nodurile au fost procesate se returneaza array-ul ce contine distantele minime de la nodul de start la toate celelalte noduri.

- **`calculateMinCost`:** Metoda care ne ajuta sa calculam costul minim al unui drum in graf, avand in vedere cerinta de a gasi un drum minim de la nodul x si un drum minim de la nodul y, ambele ajungand in nodul z. Am initializat o variabila care va stoca costul minim. Pe urma, am iterat prin toate nodurile si am verificat daca exista drumuri valide de la x la node de la y la node si de la node la z. Daca exista aceste drumuri se calculeaza costul total, iar la final se verifica daca se poate actualiza costul minim, aceasta fiind returnata la finalul executiei functiei.

### ⏳ COMPLEXITATE
- **`readEdges`:** `O(M)`
- **`writeResult`:**` O(1)`
- **`dijkstra`:** `O((N + M) * log(N))`
- **`calculateMinCost`:** `O(N)`
- **`execute`:** `O((N + M) * log(N))`
- **`main`:** `O((N + M) * log(N))`
- **COMPLEXITATE TOTALA:** `O((N + M) * log(N))`

---

### 👫 PROBLEMA 4 : SCANDAL

### 📜 DESCRIERE IMPLEMENTARE:
- **`main`:** Metoda principala care executa programul.

- **`execute`:** Metoda care ne ajuta sa citim datele de intrare din fisier, si sa afisam rezultatul final in fisierul de iesire.

- **`readInput`:** Metoda care ne ajuta sa citim datele din fisierul de intrare.

- **`writeResult`:** Metoda care ne ajuta sa scriem rezultatul obtinut in fisierul de iesire.

- **`calculateInvitations`:** Metoda care calculeaza lista de invitati. Am initializat un vector de stari pentru fiecare prieten, dupa care am iterat pentru a genera invitatii pana cand toate regulile sunt respectate. La fiecare iteratie verific daca fiecare regula este respectata pentru starea curenta de invitatie. Daca o regula nu e respectata, atunci se inverseaza starea de invitatie a unuia dintre prietenii implicati in regula respectiva. Se verifica daca toate regulile sunt respectate, iar in caz afirmativ iesim din iteratie.

- **`isConditionSatisfied`:** Metoda care verifica daca o anumita conditie este indeplinita (daca cel putin unul dintre prieteni este invitat -> c = 0; daca x este invitat sau y nu este invitat -> c = 1; daca x nu este invitat sau y este invitat -> c = 2; daca niciunul nu e invitat -> c = 3).


### ⏳ COMPLEXITATE:
- **`readInput`:** `O(M)`
- **`writeResult`:** `O(N)`
- **`calculateInvitations`:** `O(M * N)`
- **`isConditionSatisfied`:**`O(1)`
- **`execute (calculateInvitations)`:** `O(M * N)`
- **`main`:** `O(M * N)`
- **COMPLEXITATE TOTALA:** `O(M * N)`
