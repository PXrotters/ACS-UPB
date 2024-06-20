# 🎓 Tema 3 PP 2024: Lambda Calculus Interpreter

## 🎯 Scopul Temei
Implementarea unui interpretor de expresii lambda în Haskell.

## 🗂️ Structura Proiectului
### 📝 Definiția Expresiei Lambda
Vom defini o expresie lambda folosind următorul TDA:
```haskell
data Lambda = Var String
            | App Lambda Lambda
            | Abs String Lambda
```

### ⚙️ Evaluarea Expresiilor Lambda
#### 🛠 Funcții Ajutătoare
1. **vars** - Returnează o listă cu toate variabilele dintr-o expresie.
2. **freeVars** - Returnează o listă cu toate variabilele libere dintr-o expresie.
3. **newVars** - Găsește cel mai mic string lexicografic care nu apare într-o listă de string-uri.
4. **isNormalForm** - Verifică dacă o expresie este în formă normală.
5. **reduce** - Realizează β-reducerea unui redex ținând cont de coliziunile de nume.

#### 🔄 Reducerea Expresiilor Lambda
1. **normalStep** - Aplică un pas de reducere conform strategiei normale (cel mai exterior, cel mai din stânga redex).
2. **applicativeStep** - Aplică un pas de reducere conform strategiei aplicative (cel mai interior, cel mai din stânga redex).
3. **simplify** - Aplică funcția de step până când expresia rămâne în formă normală, returnând toți pașii intermediari ai reducerii.

---

### 📜 Parsing 
#### 🗂 Parsare Expresii Lambda
- **parseLambda** - Parsează un string și returnează o expresie lambda.

---

### 🚀 Pași Către un Limbaj de Programare
#### 🧩 Evaluare Expresii cu Macro-uri
- **simplifyCtx** - Evaluează o expresie care poate conține macro-uri utilizând un context computațional.

#### 🗂 Parsare Expresii cu Macro-uri
- **parseLine** - Parsează o linie de cod care poate conține macro-uri.

---

### 📚 Bibliotecă Implicită
#### 📐 Definirea Macro-urilor Uzuale
- Expresii pentru lucrul cu booleane: **`TRUE, FALSE, AND, OR, NOT, XOR.`**
- Expresii pentru lucrul cu perechi **`PAIR, FIRST, SECOND.`**
- Expresii pentru lucrul cu numere naturale **`N0, N1, N2, SUCC, PRED, ADD, SUB, MULT.`**

## 🖥️ REPL (Read-Eval-Print Loop)
Pentru a rula aplicația creată:
```sh
runhaskell main.hs
```

#### ⚙️ Comenzi utile:
- `:q` - Ieşire din REPL
- `:r` - Șterge contextul și revine la contextul implicit
- `:ctx` - Afișează contextul curent
