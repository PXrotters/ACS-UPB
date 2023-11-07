[![Review Assignment Due Date](https://classroom.github.com/assets/deadline-readme-button-24ddc0f5d75046c5622901739e7c5dd533143b0c8e959d652212380cedb1ea36.svg)](https://classroom.github.com/a/iYoQzOhX)
# Rustybox

PWD: Incercam sa obtinem calea catre directorul curent pe care il vom stoca in variabila "cwd", daca functia env::current_dir() intoarce un rezultat Ok. Daca functia intoarce un rezultat Ok vom afisa calea directorului curent utilizand metoda display(). In cazul in care nu intoarce rezultatul dorit functia env::current_dir() apelam functia exit(), care va inchide programul cu un cod de iesire (255).
ECHO: Parcurgem argumentele, excluzand primele doua elemente ale vectorului de argumente, acestea fiind comanda in sine si numele programului. Verificam daca argumentul este -n. In cazul afirmativ variabila print_newline va deveni false, altfel verificam daca trebuie sa adaugam un spatiu inainte de printarea argumentului. Pe urma, setarea variabilei print_space = true, indica faptul ca pentru urmatorul argument se va adauga un spatiu inainte de a il afisa, urmand ca argumentul sa fie afisat. La final verificam daca nu s-a intalnit argumentul -n, afisand un rand nou.
CAT: Parcurgem fisierele, excluzand primele doua elemente ale vectorului de fisiere, acestea fiind comanda in sine si numele programului. Se incearca citirea continutului fiecarui fisier specificat in parametrii folosind functia read_to_string, iar in cazul in care s-a reusit citirea (se intoarce un rezultat Ok) continutul fisierului este afisat. Altfel, se returneaza codul de eroare (236).
MKDIR: Parcurgem directoarele, excluzand primele doua elemente ale vectorului de directoare, acestea fiind comanda in sine si numele programului. Se incearca crearea fiecarui director specificat in argumente folosind functia create_dir, iar in cazul in care s-a reusit continuam programul fara a face nimic, alfel intoarcem codul de eroare (226).
MV: Verificam daca cumva avem un numar diferit de 4 argumente, fapt care conduce la returnarea codului de eroare (216), deoarece mv poate avea decat 4 argumente (argv[0], mv, src, dest). Altfel, retinem in doua variabile sursa si destinatia, dupa care vedem daca se poate realiza mutarea/redenumirea fisierului/directorului, folosind functia fs::rename. Daca operatia reuseste functia returneaza 0, in caz contrar returneaza codul de eroare (216).
LN: Verificam daca cumva avem un numar mai mic de 4 argumente, fapt care conduce la returnarea codului de eroare (216), deoarece ln trebuie sa aibe cel putin 4 argumente (argv[0], ln, src, link, optional -s/--symbolic). Altfel, retinem pozitiile surselor si destinatiilor din argumente si, de asemenea, initializam o variabila care specifica daca se doreste un link simbolic (false). Verficam daca al treilea argument este -s sau --symbolic, iar in caz afirmativ setam variabila is_symbolic la true (dorim un link simbolic) si actualizam pozitiile surselor si destinatiilor. Pe urma, extragem locatia sursa si destinatia pentru operatia de linkare si verificam daca sursa specificata exista. Daca nu exista, functia returneaza codul de eroare (206). In functie de tipul de link specificat (simbolic sau hard), incercam sa cream linkul. In caz de eroare se returneaza codul de eroare (206).
RMDIR: Verificam daca cumva avem un numar mai mic de 3 argumente, fapt care conduce la returnarea codului de eroare (196), deoarece rmdir poate avea cel putin 3 argumente (argv[0], rmdir, name1, name2,...). Altfel, pentru fiecare director din argumente, se incearca stergerea directorului respectiv. Daca se intampina o eroare in timpul stergerii, functia va returna codul de eroare (-60).
RM: Parcurgem argumentele primite, ignorand primele 2 argumente (nume program && comanda). Pentru fiecare argument verificam optiunile posibile (-r -R --recursive -d --dir). Verificam daca nu sunt specificate fisierele sau directoarele pentru stergere, caz in care se returneaza codul de eroare (186). Pentru fiecare element din vectorul files_or_dirs verificam tipul elementului (file/dir), iar in functie de tipul elementului se incearca stergerile : fisierele cu std::fs::remove_file(), directoarele cu std::fs::remove_dir_all(), in cazul in care e activata stergerea recursiva sau std::fs::remove_dir() pentru stergerea unui director gol. Orice eroare in procesul de stergere va duce la setarea unei variabile cu codul specific (-70). La final se va returna variabila respectiva care va returna codul de eroare (-70) sau 0 in cazul in care nu s-a produs nicio eroare la stergere.
LS: Parcurgem argumentele primite, ignorand primele 2 argumente (nume program && comanda). Pentru fiecare argument verificam optiunile posibile (-a -all -R -recursive -l), setand variabilele show_hidden, recursive si long_format corespunzator pe true daca este cazul. Verificam daca nu sunt furnizate alte argumente in afara de numele programului si comanda, afisand continutul directorului curent (.) folosind functia list_directory. In caz contrar, pentru fiecare cale specificata in argumente verificam daca calea specificata exista folosind fs::metadata(). Daca calea specificata este un director, afiseaza continutul acestuia folosind functia list_directory, altfel daca calea nu este un director afiseaza numele caii. Functia list_directory primeste calea si optiunile pentru afisarea continutului. Pentru fiecare intrare verificam daca numele de fisier incepe cu "."(ascuns) si daca optiunea de afisare a fisierelor ascunse nu este setata. Daca da, continuam la urmatoare iteratie. Daca este activata afisarea in format detaliat, afiseaza informatii (permisiuni, dimensiune, nume). In caz contrar, afisam numele fiserului. Daca este activata optiunea de afisare recursiva si intrarea este un director, apeleaza recursiv list_directory(), pentru acea cale. Erorile intampinate in timpul procesarii intrarilor din director conduc la returnarea codului de eroare (-80).
CP: Verificam daca cumva avem un numar mai mic de 3 argumente, fapt care conduce la returnarea codului de eroare (166), deoarece cd poate avea cel putin 3 argumente (argv[0], cd, file, dir, -r, ...). Verificam daca a fost selectata optiunea -r -R sau --recursive, in caz afirmativ setand variabila recursive la true si actualizand indexul pentru sursa si destinatie. Stabilim caile sursei si destinatiei. Daca nu exista un argument pentru destinatie, se considera implicit "doc". Apoi, cream si verificam daca exista calea sursa returnand codul de eroare (-90) in caz negativ. Se creaza si calea destinatie si se verifica tipul caii sursa (file / dir) si se efectueaza operatia de copiere. Daca sursa este un fisier si destinatia este un director, se copiaza fisierul sursa in directorul destinatie. In caz contrar, se copiaza direct fisierul sursa in locatia specificata de destinatie. Daca sursa este un director si este activata o opiune recursiva se apeleaza functia copy_dir pentru a efectua copierea. Functia copy_dir primeste doua cai (sursa si destinatie). Daca directorul destinatie nu exista se creeaza , se obtin intrarile din directorul sursa, iar pentru fiecare intrare se obtine calea sursei si calea destinatiei, apoi se verifica daca intrarea este un director. Daca este un director se creeaza directorul in destinatie si se apeleaza recursiv copy_dir pentru a copia continutul din directorul sursa in cel destinatie. Dacă este un fisier, se realizeaza copierea din sursa in destinatie folosind std::fs::copy. Erorile intampinate in timpul conduc la returnarea codului de eroare (-90).

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
