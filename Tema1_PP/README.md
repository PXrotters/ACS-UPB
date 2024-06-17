# Tema 1: Regresie Liniară 📈

---

## Descriere

Această temă implică implementarea algoritmului de regresie liniară folosind Scala, cu un accent pe stilul de programare funcțional. Regresia liniară este o tehnică de Machine Learning utilizată pentru a aproxima relația liniară între o variabilă dependentă și una sau mai multe variabile independente.

## Ce este Regresia Liniară?

Regresia liniară presupune găsirea unei drepte (în cazul unidimensional) sau a unui plan (în cazul bidimensional) care minimizează suma pătratelor diferențelor dintre valorile estimate și cele observate. Într-un caz general, ecuația pentru regresia liniară este de forma: y = a * x + b, unde `y` este variabila dependentă, `x` este variabila independentă, iar `a` și `b` sunt coeficienții care trebuie determinați.

## Structura Temei 

### 1. Seturi de Date 📊

#### 1.1. Citirea din CSV

Implementarea funcționalităților pentru citirea datelor dintr-un fișier CSV și transformarea lor într-o structură de tip Dataset, care va reține datele sub forma unei matrice.

#### 1.2. Selectare Atribute/Feature-uri

Implementarea funcțiilor pentru selectarea de coloane specifice din Dataset, pentru a le utiliza în analiza și regresia liniară.

#### 1.3. Împărțire Dataset

Implementarea funcției pentru împărțirea setului de date în două subseturi: unul pentru antrenare și unul pentru testare, folosind un procent specificat.

### 2. Operații cu Matrici 🧮

Implementarea funcțiilor de bază necesare pentru lucrul cu matrici, cum ar fi conversia din Dataset în Matrix, transpunerea matricii, operații de map, scădere și înmulțire matricială.

### 3. Regresia Liniară 📉

Implementarea algoritmului de regresie liniară folosind algoritmul Gradient Descent pentru a găsi coeficienții optimi ai ecuației liniare.

#### 3.1. Regresia pentru o Listă de Atribute

Implementarea metodei de regresie care utilizează datele de intrare specificate pentru a antrena modelul și a evalua performanța sa pe un set de date de validare separat.

#### 3.2. Plotting 📊

Generarea unui grafic pentru a vizualiza performanța modelului de regresie pe datele de testare.

## Testare 🧪

Implementările din această temă sunt validate folosind ScalaCheck pentru generarea de date random și verificarea proprietăților, și Munit pentru teste unitare.

### ScalaCheck

- Verifică corectitudinea implementărilor de Dataset și Matrix prin generarea automată a diverselor scenarii de date.

### Munit

- Testează algoritmul de Regresie Liniară pentru a asigura comportamentul corect în diferite condiții de intrare.

### Cum să rulezi testele

Folosește comanda `sbt test` în directorul principal al proiectului pentru a executa toate testele.

Adăugarea de teste suplimentare este recomandată pentru acoperirea extinsă a funcționalităților implementate.
