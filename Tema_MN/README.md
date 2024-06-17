# Tema 2 - Metode Numerice

---

## Introducere

În recunoașterea formelor și analiza datelor, utilizarea metodelor de compresie precum SVD și PCA este esențială pentru reducerea dimensionalității și extragerea caracteristicilor semnificative din seturi mari de date.

### Descompunerea valorilor singulare (SVD)

Descompunerea valorilor singulare (SVD) a unei matrice este esențială pentru compresia și aproximarea eficientă a datelor, eliminând informațiile redundante sau mai puțin semnificative.

### Compresia imaginilor folosind SVD

Compresia imaginilor prin SVD permite reprezentarea imagini aproximative cu o cantitate redusă de informații, păstrând totuși caracteristicile principale.

#### Task 1 [20p]

Funcția `task1(photo, k)` implementată în Octave comprimă o imagine utilizând descompunerea redusă a valorilor singulare (SVD), păstrând doar primele `k` valori singulare pentru a obține o imagine aproximativă.

---

## Compresia imaginilor folosind analiza componentelor principale

Analiza componentelor principale (PCA) este o altă metodă eficientă de compresie și extragere a caracteristicilor din datele complexe.

### Task 2 [20p]

Implementarea algoritmului PCA prin SVD pentru compresia imagistică, inclusiv proiecția imaginii originale în spațiul componentelor principale și reconstituirea ei cu doar primele `pcs` componente.

### Task 3 [20p]

Implementarea algoritmului PCA folosind matricea de covarianță pentru compresia imaginilor, calculând valorile și vectorii proprii, selectând apoi primele `pcs` componente principale.

---

## Task 4 : Recunoașterea cifrelor scrise de mână [35p]

Utilizarea PCA pentru recunoașterea cifrelor scrise de mână din setul de date MNIST, incluzând pregătirea datelor, compresia prin PCA și implementarea algoritmului k-nearest neighbors (KNN) pentru predicția cifrelor.

---

## Detalii implementare [5p]

În fișierul Detalii implementare.pdf (inclus în arhiva finală), sunt descrise detaliat soluțiile implementate pentru fiecare task.

---

## Observații finale

- Implementarea task-urilor s-a făcut exclusiv în limbajul Octave, respectând specificațiile impuse.
- Algoritmii PCA și SVD au fost adaptați pentru compresia eficientă a imaginilor și recunoașterea cifrelor, obținând rezultate satisfăcătoare.
- Rezultatele obținute au fost evaluate și comparate cu alternativele de machine learning, demonstrând eficiența metodelor numerice implementate.
