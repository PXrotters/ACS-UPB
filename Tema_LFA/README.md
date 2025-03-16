# 🎯 Regex Generator

## 📜 Descriere
**Regex Generator** este un program scris în **Java** care generează o **expresie regulată** (regex) capabilă să accepte cuvintele dintr-un **limbaj Accept** și să respingă cuvintele dintr-un **limbaj Fail**. Acest proiect a fost realizat ca parte a **temei LFA 2024**.

## 📥 Intrare
Programul citește datele dintr-un fișier `input.txt` care are următorul format:
- **Prima linie**: trei numere întregi:
  - `cnt_accept` - numărul de cuvinte din limbajul Accept
  - `cnt_fail` - numărul de cuvinte din limbajul Fail
  - `len_string` - lungimea fiecărui cuvânt (toate au aceeași lungime)
- **Următoarele `cnt_accept` linii**: cuvintele din limbajul Accept
- **Ultimele `cnt_fail` linii**: cuvintele din limbajul Fail

### 🔍 Exemplu `input.txt`
```
3 2 4
baed
bece
bace
bacd
aace
```

## 📤 Ieșire
Programul generează un regex și îl scrie în `output.txt` cu următorul format:
- **Prima linie**: cuvântul `regex`
- **A doua linie**: expresia regulată generată

### 🔍 Exemplu `output.txt`
```
regex
b.(ed|ce)
```

## 🚀 Funcționalități
- 📂 **Citirea fișierului de intrare** și extragerea cuvintelor din cele două limbaje.
- 🔗 **Gruparea cuvintelor** după prefixe comune pentru optimizarea expresiei regulate.
- 🔍 **Generarea unei expresii regulate minimale** care acoperă toate cuvintele acceptate și exclude cele din Fail.
- 📄 **Scrierea regex-ului în fișierul de ieșire**.

## 🛠️ Cum se rulează
1. Asigură-te că ai instalat **Java 8+**.
2. Compilează programul:
   ```sh
   javac RegexGenerator.java
   ```
3. Rulează programul:
   ```sh
   java RegexGenerator
   ```
4. Pentru a rula testele automat, poți folosi scriptul checker.sh din directorul checker:
   ```sh
   ./checker/checker.sh
   ```

## 🏆 Optimizare
Programul determină **lungimea optimă a prefixului** pentru a obține un regex cât mai scurt, folosind o metodă euristică.

## 📌 Tehnologii folosite
- **Java** ☕
- **Structuri de date eficiente** (`List`, `Set`, `Map`)
- **Stream API** pentru procesarea optimizată a listelor
- **Expresii regulate** 📖

## 📖 Referințe
- Tema LFA 2024: [Link GitLab](https://gitlab.cs.pub.ro/vlad_adrian.ulmeanu/tema-lfa-2024-ca-cd-clasificator-public)
- Testare regex: [regex101](https://regex101.com/)

## 👨‍💻 Autor
📌 **Lemnaru Mihai-Daniel** - [@PXrotters](https://github.com/PXrotters)
