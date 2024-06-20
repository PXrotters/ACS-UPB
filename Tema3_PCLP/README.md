# 📋 Tema 3: Miniprocesor

## 📝 Descrierea temei
Această temă constă în implementarea unui interpretor de biți similar unui procesor, cu capacitatea de a decodifica și executa instrucțiuni simple de adunare, scădere, înmulțire și împărțire. Tema este împărțită în mai multe task-uri care trebuie rezolvate în ordine.

### 🧩 Task 1: Decodificare Instrucțiune
Implementarea unui program care decodifică o instrucțiune dată în format binar și afișează numărul de instrucțiuni, operatorii și dimensiunea operanzilor.
- Programul citește un număr unsigned int de la tastatură și îl decodifică conform formatului specificat.
- Afișează numărul de instrucțiuni, operatorii și dimensiunea operanzilor.

---

### 🛠️ Task 2: Executare Instrucțiune
Extinderea programului pentru a citi operanzi de la tastatură, a decodifica instrucțiunea și a executa operațiile în ordinea primirii acestora.
- Extinde task-ul 1 pentru a citi operanzi de la tastatură.
- Calculează rezultatul executând operațiile în ordinea primirii acestora.

---

### ⚙️ Bonus 1: Operanzi cu dimensiuni ciudate
Extinderea programului pentru a executa instrucțiuni ale căror operanzi pot avea dimensiuni variabile în intervalul [1, 16].

---

### 🔄 Bonus 2: Precedenta operatorilor
Implementarea precedenței operatorilor astfel încât * și / au precedență egală între ei, dar mai mare decât + și -.

## 🚀 Comenzi de compilare și rulare
Pentru a compila și rula programele, folosiți Makefile-ul inclus. Exemple de comenzi:
```bash
make task1
./task1
make task2
./task2
```
