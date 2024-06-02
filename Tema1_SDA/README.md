# 🎩 Banda Magică

Banda magică este implementată folosind o listă dublu înlănțuită cu sentinelă. De asemenea, se folosește un nod special pentru a reprezenta degetul (poziția curentă în bandă).

## 🖐️ Degetul

Degetul este reprezentat printr-un nod special în lista dublu înlănțuită. Acesta indică poziția curentă în bandă și este marcat cu caracterul `#`.

### 🛠️ Operatii: MOVE_LEFT, MOVE_RIGHT, INSERT_LEFT, INSERT_RIGHT, MOVE_LEFT_CHAR, MOVE_RIGHT_CHAR

Pentru fiecare operație, există funcții dedicate care efectuează operația respectivă pe banda magică.

## 💾 Stiva pentru UNDO și REDO

Stiva este folosită pentru a memora stările anterioare și viitoare ale benzii magice, permițând operații de UNDO și REDO.

---

În fișierul principal, se deschid fișierele pentru citire și scriere, iar apoi se parcurg comenzile și se efectuează operațiile corespunzătoare.

Pentru fiecare operație, se verifică și se gestionează corect starea stivei și a cozii.

## 📝 Verificări și afișare

La final, se verifică și se afișează rezultatul fiecărei operații, iar erorile sunt gestionate corespunzător.

---

La final, se eliberează memoria alocată pentru toate structurile de date folosite.

## 🧹 Curățenie finală

Se eliberează memoria alocată pentru lista dublu înlănțuită, coadă și stive.
