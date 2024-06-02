[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/iYoQzOhX)
# 🛠️ Rustybox

## 🚀 Funcționalități

### 📂 PWD (Print Working Directory)
- **Descriere**: Obține calea către directorul curent.
- **Implementare**: Dacă `env::current_dir()` returnează un rezultat `Ok`, afișează calea directorului folosind metoda `display()`. În caz de eroare, programul se închide cu codul de ieșire 255.

### 📢 ECHO
- **Descriere**: Afișează argumentele primite, cu opțiunea de a omite newline-ul final.
- **Implementare**: 
  - Exclude primele două argumente (`argv[0]` și comanda).
  - Verifică dacă argumentul este `-n`. Dacă da, `print_newline` devine `false`.
  - Adaugă spațiu înaintea fiecărui argument următor.
  - Afișează fiecare argument și, dacă `-n` nu este prezent, adaugă un newline la final.

### 📄 CAT
- **Descriere**: Afișează conținutul fișierelor specificate.
- **Implementare**: 
  - Exclude primele două argumente (`argv[0]` și comanda).
  - Citește conținutul fiecărui fișier folosind `read_to_string`.
  - Afișează conținutul dacă citirea este reușită, altfel returnează codul de eroare 236.

### 📁 MKDIR
- **Descriere**: Creează directoare.
- **Implementare**: 
  - Exclude primele două argumente (`argv[0]` și comanda).
  - Creează fiecare director specificat folosind `create_dir`.
  - În caz de eroare, returnează codul de eroare 226.

### 📨 MV (Move)
- **Descriere**: Mută sau redenumește un fișier/director.
- **Implementare**: 
  - Verifică dacă sunt exact 4 argumente (`argv[0]`, `mv`, `src`, `dest`).
  - Mută/redenumește folosind `fs::rename`.
  - Returnează 0 la succes sau codul de eroare 216 în caz de eroare.

### 🔗 LN (Link)
- **Descriere**: Creează linkuri simbolice sau hard.
- **Implementare**: 
  - Verifică dacă sunt cel puțin 4 argumente (`argv[0]`, `ln`, `src`, `link`, opțional `-s/--symbolic`).
  - Verifică și setează tipul de link (simbolic sau hard).
  - Creează linkul corespunzător și returnează 0 la succes sau codul de eroare 206 în caz de eroare.

### 🗑️ RMDIR (Remove Directory)
- **Descriere**: Șterge directoare goale.
- **Implementare**: 
  - Verifică dacă sunt cel puțin 3 argumente (`argv[0]`, `rmdir`, `name1`, `name2`, ...).
  - Șterge fiecare director specificat.
  - Returnează codul de eroare 196 în caz de eroare.

### ❌ RM (Remove)
- **Descriere**: Șterge fișiere și directoare.
- **Implementare**: 
  - Exclude primele două argumente (`argv[0]` și comanda).
  - Verifică opțiunile posibile (`-r -R --recursive -d --dir`).
  - Șterge fișierele/directoarele specificate și returnează codul de eroare 186 sau 70 în caz de eroare.

### 📋 LS (List)
- **Descriere**: Listează conținutul directoarelor.
- **Implementare**: 
  - Exclude primele două argumente (`argv[0]` și comanda).
  - Verifică opțiunile posibile (`-a -all -R -recursive -l`).
  - Listează conținutul directorului curent dacă nu sunt furnizate alte argumente.
  - Listează detaliat sau recursiv conținutul în funcție de opțiuni.
  - Returnează codul de eroare 80 în caz de eroare.

### 📋 CP (Copy)
- **Descriere**: Copiază fișiere și directoare.
- **Implementare**: 
  - Verifică dacă sunt cel puțin 3 argumente (`argv[0]`, `cp`, `file`, `dir`, `-r`, ...).
  - Setează opțiunea recursivă dacă este specificată.
  - Copiază sursa în destinație și returnează codul de eroare 90 în caz de eroare.

## 🧪 Verify

Pentru a testa tema, urmați pașii de mai jos:

### 1. Instalare NodeJS (este instalat în codespace)

```bash
# Clonează repository-ul de teste
git submodule update --init 

# Actualizează repository-ul de teste la ultima versiune
cd tests
git pull 
cd ..

# Instalează lodash
npm install lodash


## Verify

Run the following commands to test your homework:

You will have to install NodeJS (it is installed in the codespace)

```bash
# Clone tests repository
git submodule update --init 

# Update tests repository to the lastest version
cd tests
git pull 
cd ..

# Install loadash
npm install lodash
```

Install rustybox

```bash
cargo install --path .
```

If the `rustybox` command can't be found, be sure to add the default cargo installation folder into the PATH environment variable

```bash
export PATH=/home/<your username here>/.cargo/bin:$PATH
```

Run tests

```bash
cd tests
# Run all tests 
./run_all.sh

# Run single test
./run_all.sh pwd/pwd.sh
```
