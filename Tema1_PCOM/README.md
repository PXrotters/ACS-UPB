# 🖥️ Tema 1: Protocoale de Comunicații

**Lemnaru Mihai-Daniel**  
**Grupa: 322 CD**

---

## 📋 Descrierea Proiectului

### 🌐 Structura `packet`

Am creat o structură `packet` care reține informații despre un pachet care urmează să fie trimis mai departe.

### 📜 Funcții

#### `ip_address_to_int`
- **Descriere**: Primește ca parametru un șir de caractere ce reprezintă o adresă IP și returnează valoarea întreagă corespunzătoare acelei adrese IP în format Big Endian.
- **Implementare**: 
  - Inițializează variabila `new_ip_address` cu 0.
  - Parcurge fiecare caracter din șirul adresei IP.
  - Când întâlnește un ".", mută valoarea stocată la stânga cu 8 biți pentru a face loc noului octet.
  - Combină valoarea octetului curent cu valoarea stocată anterior folosind "OR".
  - Actualizează valoarea octetului dacă caracterul curent este o cifră.
  - Adaugă ultimul octet la adresa IP calculată.

#### `get_arp_table_entry`
- **Descriere**: Primește ca parametri o adresă IP de căutat, tabela ARP și lungimea tabelei, și returnează un pointer către intrarea respectivă sau NULL altfel.

#### `binary_search`
- **Descriere**: Realizează o căutare binară în tabela de rutare pentru a găsi cea mai specifică rută pentru o anumită adresă IP destinație.
- **Complexitate**: `O(log n)`

#### `best_route`
- **Descriere**: Returnează un pointer către cea mai specifică intrare din tabela de rutare care se potrivește cu adresa IP destinație.

#### `send_icmp`
- **Descriere**: Construiește și trimite un pachet ICMP pe o anumită interfață.
- **Implementare**: 
  - Extrage header-ul Ethernet, IP și ICMP din buffer-ul de intrare.
  - Copiază conținutul întregului pachet ICMP într-un nou buffer.
  - Actualizează adresele MAC și campurile pachetului.
  - Calculează checksum-ul pachetului IP și ICMP.
  - Copiază pachetul ICMP înapoi în buffer-ul original și transmite-l pe interfața specificată.

#### `comparator`
- **Descriere**: Folosit de `qsort` pentru a sorta intrările din tabela de rutare în funcție de masca de rețea (descrescător) și prefixul rețelei (crescător).

#### `arp_reply`
- **Descriere**: Construiește și trimite un răspuns de tip ARP către o adresă IP specificată.
- **Implementare**: 
  - Inițializează un nou antet ARP și completează campurile acestuia.
  - Copiază adresele MAC și IP în buffer.
  - Calculează lungimea totală a pachetului și trimite-l prin interfața specificată.

### 📝 Funcția `main`

- **Descriere**: 
  - Inițializează un buffer `buf` de dimensiunea maximă a pachetului, o coadă `queue`, și alocă memorie pentru tabela ARP și tabela de rutare.
  - Sortează tabela de rutare folosind `qsort` și comparatorul descris anterior.
  - Primește un pachet de pe orice interfață și îl salvează în buffer-ul `buf`, lungimea pachetului fiind stocată în `len`.
  - Obține adresa header-ului Ethernet din buffer și verifică tipul protocolului.

- **Manipularea Pachetelor IP**: 
  - Obține adresa header-ului IP din buffer.
  - Setează checksum-ul IP la 0 înainte de recalculare și verifică integritatea.
  - Determină cea mai bună rută pentru adresa IP de destinație.
  - Verifică și trimite mesaje ICMP corespunzătoare pentru diferite cazuri (TTL, destinație inaccesibilă, răspuns ICMP).

- **Manipularea Pachetelor ARP**:
  - Răspunde la cererile ARP cu pachete ARP Reply.
  - Actualizează tabela ARP locală cu informațiile primite din ARP Reply.
  - Trimite pachetele aflate în coadă către destinație folosind adresa MAC obținută.

---

✍️ **Documentația este realizată pentru a facilita înțelegerea și utilizarea funcțiilor descrise.**
