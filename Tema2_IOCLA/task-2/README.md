# Task 2 - Processes

Prin intermediul acestui task se doreste aprofundarea lucrului cu structuri.

Se da structura simplificata a unui proces:

```c
    struct proc{
        short pid;
        char prio;
        short time;
    };
```

---

## Exercitiul 1

Pentru aceasta parte a task-ului aveti de implementat functia `sort_procs()`
in fisierul *sort-procs.asm* care va simula sortarea tuturor proceselor active in momentul curent.

Pentru a intelege mai bine cum functioneaza un proces, vom explica mai jos ce inseamna fiecare field al structurii `proc`:

- Field-ul `pid` reprezinta id-ul unui proces care este prezent in sistem, fie el activ sau inactiv la momentul curent, acest id este unic fiecarui proces
- Field-ul `prio` reprezinta prioritatea pe care o are un proces atunci cand acesta ruleaza pe procesor. Fiecare proces are o astfel de prioritate, de la 1 la 5, 1 reprezentand prioritate maxima de rulare, iar 5 reprezentand prioritate minima de rulare. In functie de aceasta prioritate, procesele ajung sa ruleze mai devreme sau mai tarziu pe procesor
- Field-ul `time` reprezinta cuanta de timp acordata fiecarui proces in parte de a rula pe procesor. Desi veti intalni valori destul de mari in acest field pentru testare, in realitate nu exista cuante atat de mari de rulare, deoarece ar deveni unfair pentru restul proceselor sa astepte atat timp dupa un altul

Pentru a sorta procesele, stabilim urmatoarele reguli:

- Procesele trebuie sa apara in ordine crescatoare procesele in functie de prioritate
- Pentru procesele cu aceeasi prioritate, acestea se vor ordona crescator in functie de cuanta de timp
- Pentru procese cu aceeasi prioritate si cu aceeasi cuanta de timp, acestea vor fi ordonate crescator dupa id

Sortarea se va face **in place**, adica vectorul `procs` prezentat mai jos va trebui, in urma apelului functiei, sa fie sortat. Antetul functiei este:

```
void sort_procs(struct proc *procs, int len);
```

Semnificatia argumentelor este:

- **procs** adresa de inceput a vectorului de procese
- **len** numarul de procese aflate in sistem

**Atentie!** Nu puteti folosi functii externe pentru a sorta vectorul.

---

## Exercitiul 2

In continuarea exercitiului 1, acum trebuie sa implementati functia `run_procs()` in
fisierul *run_procs.asm* care va calcula intr-un mod simplificat timpul mediu de rulare pentru fiecare prioritate, adica va trebui sa calculati suma cuantelor de timp pentru o prioritate si apoi sa o impartiti la numarul de procese care au acea prioritate.

Pentru acest task va trebui sa declarati o structura `avg`, care va stoca catul impartirii sumei cuantelor de timp la numarul de procese, iar `remain` va stoca restul acestei impartiri:

```
    struct avg{
        short quo;
        short remain;
    };
```

Va trebui sa puneti valorile obtinute in vectorul `avg_out` prezentat mai jos, pe prima pozitie aflandu-se rezultatul pentru prioritatea 1, iar pe ultima rezultatul pentru prioritatea 5. Antetul functiei este:

```
void run_procs(struct proc* procs, int len, struct avg *avg_out);
```

Semnificatia argumentelor este:

- **procs** adresa de inceput a vectorului de procese
- **len** numarul de procese aflate in sistem
- **avg_out** adresa de inceput a vectorului de structuri `avg`

**Se garanteaza ca toate valorile raman in limitele tipurilor de date date in structura, adica `quo` si `remain` nu vor fi numere mai mari de 16 biti.**

## **Observatie**

Pentru exercitiul 2 se va folosi acelasi vector folosit si la exercitiul 1. Daca anumite valori se modifica in urma exercitiului 1, atunci exercitiul 2 nu va putea fi rezolvat corect. Exercitiile sunt independente totusi, puteti alege sa nu faceti primul exercitiu, dar veti primi doar jumatate din punctajul aferent acestui task.

---