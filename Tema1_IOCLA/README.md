# 🏎️ Tema 1: To Pit or Not to Pit... This is the Strategy

## 📄 Descriere

Aceasta tema simulează strategia de gestionare a senzorilor într-o echipă de Formula 1. Echipa Ferrari se confruntă cu probleme cauzate de senzori defecte care transmit date eronate. Sarcina ta este să implementezi un program care să gestioneze aceste date și să ajute echipa să ia decizii corecte în timpul curselor.

## 📂 Structura Proiectului

- `main.c`: Conține implementarea principală a programului.
- `operations.c`: Conține implementarea funcțiilor de operare asupra senzorilor.
- `structs.h`: Conține definițiile structurilor utilizate în program.
- `Makefile`: Fisierul Makefile pentru compilare, rulare și curățarea proiectului.

## ⚙️ Funcționalități

### 1. 📋 Printare simplă (`print <index>`)
Afișează datele senzorului de la poziția specificată. Dacă indexul este invalid, se afișează mesajul "Index not in range!".

### 2. 📝 Printare cu priorități
Afișează datele tuturor senzorilor, ordonându-i după tipul acestora (PMU înaintea Tire Sensor).

### 3. 🔍 Analyze (`analyze <index>`)
Efectuează toate operațiile asociate senzorului de la poziția specificată. Dacă indexul este invalid, se afișează mesajul "Index not in range!".

### 4. 🧹 Clear (`clear`)
Șterge din vectorul de senzori pe cei care conțin valori eronate, conform condițiilor specificate.

### 5. 🚪 Exit (`exit`)
Eliberează memoria și închide programul.

## 📐 Structuri

### Sensor
```c
enum sensor_type {
    TIRE, PMU
};

typedef struct {
    enum sensor_type sensor_type; // 0/1
    void *sensor_data; // TireSensor/PowerManagementUnit
    int nr_operations;
    int *operations_idxs;
} Sensor;
```

### TireSensor
```c
typedef struct __attribute__((__packed__)) {
    float pressure; // 19-26 psi
    float temperature; // between 0-120C
    int wear_level; // between 0% and 100%
    int performace_score; // between 1-10
} TireSensor;
```

### PowerManagementUnit
```c
typedef struct __attribute__((__packed__)) {
    float voltage; // 10-20V
    float current; // -100 to 100A
    float power_consumption; // 0 to 1000 kW
    int energy_regen; // 0-100%
    int energy_storage; // 0-100%
} PowerManagementUnit;
```

## 🛠️ Compilare și Rulare
### Comenzi Makefile
- make: Compilează proiectul.
- make run: Rulează programul.
- make clean: Curăță fișierele generate în urma compilării.
- make check: Verifică corectitudinea gestionării memoriei folosind Valgrind.

## 🧹 Managementul Memoriei
Programul alocă și dezalocă dinamic memoria pentru toate structurile utilizate. În urma operației clear, memoria pentru senzorii eliminați este eliberată și vectorul de senzori este redimensionat.

## 💡 Stil de Cod și Comentarii
Codul este scris conform bunelor practici de programare, cu comentarii explicative pentru funcțiile și structurile principale.
