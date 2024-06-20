# ✈️ Tema 2: Avioane

## 🚀 Introducere
### Despre Avioane
Avioanele pot fi de 2 tipuri:
- Ele pot avea capul îndreptat în 4 direcţii: Nord (N), Sud (S), Est (E), Vest (W).

### Despre Obstacole
Obstacolele sunt de dimensiune 1 x 1 şi sunt alese pentru a încurca adversarul.

## 📋 Cerinţe

Datele sunt stocate într-un vector generic `void *info`, păstrând pentru fiecare avion, în ordine, următoarele informaţii:
- Linia şi coloana pe care se găseşte capul avionului, păstrate pe câte doi octeţi fiecare (atât linia, cât şi coloana sunt numere naturale din intervalul [0, N - 1]).
- Direcţia spre care se deplasează avionul (N, S, E, W), păstrată pe un octet.
- Patru caractere care reprezintă codul avionului, astfel: primul caracter reprezintă tipul avionului ('1', '2'), următoarele trei caractere reprezintă codul aeroportului din care şi-au imaginat fiecare că o să zboare avionul.
- Viteza de deplasare (v poziţii/secundă), păstrată pe patru octeţi.

### ✅ Task 1
```c
void SolveTask1(void *info, int nr_avioane)
```

Funcţia afişează informaţiile despre fiecare avion din info în ordine.

---

### ✨ Task 2
```c
void SolveTask2(void *info, int nr_avioane, int N, char **mat)
```
Funcţia completează matricea mat cu caractere '*', unde se găsesc avioanele şi cu caractere '.', în caz contrar.

---

### 🔄 Task 3
```c
void SolveTask3(void *info, int nr_avioane)
```
Funcţia sortează avioanele conform criteriilor specifice şi afişează informaţiile sortate.

---

### 🛡️ Task 4
```c
void SolveTask4(void *info, int nr_avioane, int nr_obstacole, int *x, int *y, int N)
```
Funcţia calculează câte avioane pot să se deplaseze în siguranţă până la marginea hărţii, fără a lovi vreun obstacol.

---

### ⏳ Bonus: Task 5
```c
void SolveTask5(void *info, int nr_avioane, int T, int nr_pct_coord, int *X, int *Y, int N)
```
Funcţia afişează numărul de avioane în punctele date de coordonatele din X și Y pentru fiecare moment de timp de la 0 la T.

## 📦 Resurse
- Checker-ul, scheletul de cod și testele se găsesc în arhiva avioane.zip.
- Pentru instalarea programelelor necesare verificării coding style-ului, executați:
```bash
chmod +x install-linters.sh check.sh
./install-linters.sh
```
