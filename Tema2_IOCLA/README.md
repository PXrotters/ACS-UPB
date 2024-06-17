# Tema 2 - The race is on 🏁

## Descriere

Tema constă în implementarea a patru exerciții independente și un exercițiu bonus în limbaj de asamblare. Fiecare exercițiu necesită implementarea unor funcții specifice, utilizând doar resursele și instrucțiunile specificate.

## Structura temei 📋

Tema este împărțită în următoarele task-uri și exerciții:

1. **Task 1 - Simple cipher (10p)**
   - Implementarea funcției `simple()` pentru criptarea unui text folosind un cifru simplu de deplasare.

2. **Task 2 - Processes (25p)**
   - **Exercițiul 1:** Implementarea funcției `sort_procs()` pentru sortarea proceselor în funcție de prioritate, timp și ID.
   - **Exercițiul 2:** Implementarea funcției `run_procs()` pentru calcularea timpului mediu de rulare pentru fiecare prioritate.

3. **Task 3 - ENIGMA MACHINE (25p)** (Task neimplementat)

4. **Task 4 - Checkers (30p)**
   - Implementarea funcției `checkers()` pentru calcularea pozițiilor posibile ale unei piese de dame pe o tablă de joc de 8x8.

5. **Bonus - Optimized checkers (20p)**
   - Bonusul constă în optimizarea reprezentării și calculului pozițiilor posibile ale unei piese de dame pe o tablă de joc de 8x8, folosind conceptul de Bitboard în limbajul de asamblare.

## Depunere și evaluare 📥

- Implementarea fiecărui task trebuie realizată în fișierele respective menționate în enunț.
- Pentru a compila și rula testele, folosiți scriptul `checker.sh`.
  ```bash
  python3 local_checker.py --all

- Pentru a testa un task individual:
  ```bash
  python3 local_checker.py -t <număr_task>

- Arhivați tema corect folosind comanda:
  ```bash
  python3 local_checker.py --zip

## Notare 📝

Punctajul final include evaluarea automată (90p) și respectarea stilului de codare și a comentariilor (10p).
Nu sunt permise apeluri de funcții externe sau apeluri de sistem în implementare.
Respectați structura și numele fișierelor conform specificațiilor din enunț pentru a evita depunctări.
