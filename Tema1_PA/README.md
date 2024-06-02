# 🖥️ Tema 1 PA

**Lemnaru Mihai-Daniel**  
**Grupa: 322 CD**

---

## 📋 Probleme

### 1️⃣ Problema 1: Alimentare Servere

#### 📖 Descriere Implementare:

- **`optimalMaxPower`**: Metodă care calculează puterea maximă în funcție de un factor din intervalul cu capătul din stânga cel mai mic element din vectorul curent și capătul din dreapta cel mai mare din vectorul curent. Această putere maximă este minimul dintre toate alimentările cu factorul curent.
- **`binarySearch`**: Metodă care găsește puterea maximă optimă prin căutarea unui factor optim. Aplicăm algoritmul căutării binare, setând mijlocul intervalului curent și calculând puterea maximă pentru vecinii mijlocului curent pentru a decide în ce parte continuăm căutarea.
- **`main`**: Citește datele de intrare și afișează rezultatul.

#### ⏳ Complexitate:

- **`optimalMaxPower`**: `O(N)` -> Parcurgem vectorul pentru a afla puterea maximă.
- **`binarySearch`**: `O(N log N)` -> `O(2N) = O(N)` pentru parcurgerea vectorului, `O(log N)` pentru împărțirea intervalului, `O(5N) = O(N)` pentru apelurile metodei `optimalMaxPower`.
- **`main`**: `O(N log N)` -> `O(2N) = O(N)` pentru citirea vectorilor, `O(N log N)` pentru apelul `binarySearch`.
- **Complexitate Totală**: `O(N log N)`

---

### 2️⃣ Problema 2: Colorare

#### 📖 Descriere Implementare:

- **`fastExp`**: Metodă pentru calculul rapid al exponentierii modulare folosind Divide et Impera. Realizează o exponentiere recursivă și calculează pătratul rezultatului.
- **`main`**: Citește numărul natural `K` și prima pereche de forma `X T`, calculează suma tuturor posibilităților de colorare în funcție de tipul `T`.

#### ⏳ Complexitate:

- **`fastExp`**: `O(log(exp))` -> Apel recursiv cu `exp/2`.
- **`main`**: `O(K log(exp))` -> `O(K)` pentru parcurgerea grupurilor de input, `O(log(exp))` pentru apelul `fastExp`.
- **Complexitate Totală**: `O(K log(exp))`

---

### 3️⃣ Problema 3: Compresie

#### 📖 Descriere Implementare:

- **`compression`**: Metodă pentru reținerea compresiei a două șiruri de numere folosind o abordare Greedy cu sume parțiale.
- **`main`**: Citește cele două șiruri, realizează compresia și afișează lungimea șirului rezultat sau `-1` dacă nu se poate efectua compresia.

#### ⏳ Complexitate Totală:

- `O(n + m)` -> Citirea și iterarea prin ambele șiruri de numere (`n` - lungimea primului șir, `m` - lungimea celui de-al doilea șir).

---

### 4️⃣ Problema 4: Criptat

#### 📖 Descriere Implementare:

- **`generateEncryptedPassword`**: Metodă care creează o parolă folosind o listă de cuvinte și un caracter. Calculează lungimea potențială a parolei și determină cea mai mare parolă posibilă.
- **`main`**: Citește cuvintele din fișier și actualizează frecvența caracterelor într-un HashMap. Generează cea mai bună parolă curentă folosind `generateEncryptedPassword` și reține lungimea celei mai mari parole.

#### ⏳ Complexitate:

- **`generateEncryptedPassword`**: `O(N * L)` -> Parcurgerea listei de cuvinte pentru numărarea aparițiilor caracterului.
- **`main`**: `O(N * L)` -> Citirea datelor de intrare și parcurgerea fiecărui caracter, plus parcurgerea tuturor caracterelor pentru generarea parolei.
- **Complexitate Totală**: `O(N * L)`

---

### 5️⃣ Problema 5: Oferta

#### 📖 Descriere Implementare:

- **`halfPrice` și `fullPrice`**: Metode care calculează prețul obținut prin gruparea produselor cu reducere de 50% sau 100%.
- **`minIndex`**: Metodă care determină indexul minim al unei liste.
- **`generateCombinations`**: Metodă care generează toate combinațiile posibile ale produselor pentru a obține prețul minim.
- **`calculateOfferPrice`**: Metodă care citește datele din fișier și calculează prețul ofertei. Stochează toate combinațiile de prețuri posibile și returnează prețul minim.
- **`main`**: Scrie rezultatul obținut în fișierul de ieșire.

#### ⏳ Complexitate:

- **`halfPrice` și `fullPrice`**: `O(1)`
- **`minIndex`**: `O(N)`
- **`generateCombinations`, `calculateOfferPrice` și `main`**: `O(N * K)`
- **Complexitate Totală**: `O(N * K)`

---

✍️ **Documentația este realizată pentru a facilita înțelegerea și utilizarea algoritmilor descriși.**
