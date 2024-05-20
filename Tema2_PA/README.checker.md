# Proiectarea Algoritmilor - Temă

Acest document conține informații utile pentru interacțiunea cu checker-ul.

## Rularea checker-ului

Rulați checker-ul din scriptul `check`. Pentru mai multe detalii, executați
`./check help`:

```text
Usage:
       ./check                 # run the entire homework
       ./check task_id         # run only one problem (e.g. number or name)
       ./check cs              # run only the coding style check
```

## Compilarea și rularea soluțiilor

Checker-ul compilează și rulează singur soluțiile, dar pentru asta are nevoie de
un `Makefile` cu format fix.

Regulile pe care le așteaptă checker-ul sunt:

- `build` - această regulă compilează toate soluțiile voastre
- `run-p1`, `run-p2` etc. - fiecare regulă rulează soluția unui exercițiu,
  **fără să o recompileze**
- `clean` - șterge programele compilate, fișierele generate de comanda `build`

Puteți scrie fișierul `Makefile` cum doriți, dar găsiți un exemplu "automatizat"
în `Makefile.template`. Dacă nu funcționează, sau dacă doriți exemple mai
"manuale", vedeți și `Makefile.exampleCpp` sau `Makefile.exempleJava`.

Puteți rezolva probleme diferite în limbaje diferite, se va schimba modul în
care compilați și rulați fiecare soluție.

**Nu ștergeți fișierul `Makefile.PA`, el face parte din checker.**

## Legendă checker

- `Run time error` - eroare apărută în timpul rulării unui test
- `TLE` - time limit exceeded (s-a depășit limita de timp a testului curent)
- `WA` - wrong answer (valoarea din fișierul `.out` diferă de cea din `.ref`)

## IO

Citiți și scrieți din fișierele indicate în cerință, care de obicei au numele
problemei. E suficient să hardcodați numele din cerință, nu trebuie căi mai
complicate. Checker-ul se asigură că există fișierele când îl rulați.

Exemple de IO în C++ și Java la problema "gigel" (puteti implementa și altfel):

```cpp
int main() {
    ifstream fin("gigel.in");
    ofstream fout("gigel.out");
}
```

```java
public class Gigel {
    public static void main(String[] args) throws IOException {
        var in = new MyScanner(new FileReader("gigel.in"));
        try (var out = new PrintStream("gigel.out")) {
        }
    }

    // Definiție MyScanner copiată.
}
```

## Exemplu debugging

Presupunem că după ce rulăm `./check`, obținem rezultatul `WA` la problema
"gigel", pe testul 4.

Ne sunt utile aceste fișiere:

- `public_tests/gigel/input/4-gigel.in` - datele de intrare ale testului
- `public_tests/gigel/out/4-gigel.out` - rezultatul soluției studentului
- `public_tests/gigel/ref/4-gigel.ref` - răspunsul corect

Uneori e nevoie să rulăm un test așa cum o face checker-ul, de exemplu pentru a
găsi probleme cu Makefile-ul sau IO. Încercați secvența asta de instrucțiuni:

```shell
make clean  # Ștergem executabilele, ca să pornim de la zero.
make build  # Compilarea trebuie să nu dea erori.

# Aducem un fișier de input în directorul curent.
cp public_tests/gigel/input/4-gigel.in gigel.in
# Executăm soluția ca checker-ul (presupunem că "gigel" este problema 1).
make run-p1
# Verificăm output-ul.
cat gigel.out
```

## Coding style

Checker-ele de coding style se găsesc pe Internet, dar și local:

- [C/C++](https://google.github.io/styleguide/cppguide.html):
  `_utils/coding_style/check_cpp.py`
- [Java](http://checkstyle.sourceforge.net/google_style.html):
  `_utils/coding_style/check_java.jar`

## Timpi de execuție

Timpii de execuție pentru problema `$id` se găsesc în:

- C/C++: `_utils/timeout/c.timeout$id`
- Java: `_utils/timeout/java.timeout$id`
