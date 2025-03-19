# 🛰️ Switch Implementation - VLAN & STP

📌 **Autor**: Lemnaru Mihai-Daniel  
📌 **Grupa**: 331 CD  

---

## 📖 Descrierea Temei  

Această temă presupune implementarea funcționalităților unui **switch Ethernet**, incluzând:  

- 🔄 **Procesul de comutare** (MAC learning & forwarding)  
- 🌐 **VLAN (Virtual Local Area Networks)**  
- 🏗️ **STP (Spanning Tree Protocol) pentru prevenirea buclelor în rețea**  

---

## ⚙️ Instalare și Setup  

🖥️ Pentru a putea rula simularea folosind **Mininet**, trebuie să ai instalat:  

```bash
sudo apt update
sudo apt install mininet openvswitch-testcontroller tshark python3-click python3-scapy xterm python3-pip
sudo pip3 install mininet
```

##💡 Fix pentru Mininet (dacă întâmpini eroarea legată de portul 6653):

```bash
pkill ovs-test
```

# 🏗️ Structura Proiectului  

## 📂 Fișiere principale:  

- **`switch.py`** → Implementarea switch-ului  
- **`configs/`** → Configurațiile pentru VLAN-uri și STP  
- **`checker/`** → Scripturi pentru testare  

## 📄 Fișiere de interes:  

- **`README.md`** → Acest fișier 📜  
- **`Makefile`** → Rulează și compilează codul  

---

# 🚀 Funcționalități Implementate  

## 🛠️ Procesul de comutare (MAC Learning & Forwarding)  

📌 Switch-ul memorează interfețele asociate adreselor MAC și redirecționează pachetele în consecință.  

✔️ Dacă MAC-ul destinație este cunoscut → **Forward direct**  
✔️ Dacă MAC-ul nu este cunoscut → **Broadcast pe toate porturile**  

---

## 🌍 Suport pentru VLAN-uri (802.1Q)  

📌 Implementarea **VLAN Tagging** permite izolarea logică a dispozitivelor.  

✔️ **Porturi de tip Access** → Legate la un singur VLAN  
✔️ **Porturi de tip Trunk** → Transportă pachete pentru mai multe VLAN-uri  

---

## 🔀 Spanning Tree Protocol (STP - 802.1D)  

📌 STP este folosit pentru **evitarea buclelor în rețea**, alegând un **root bridge** și blocând porturile redundante.  

✔️ **Root Bridge Election** → Switch-ul cu **prioritatea** cea mai mică devine **root**  
✔️ **Blocking/Forwarding ports** → Se blochează link-urile care pot duce la bucle  

---

# 🔧 Implementare Funcții Importante  

## 📌 `parse_ethernet_header(frame: bytes) -> tuple`  
📌 **Analizează un antet Ethernet și extrage:**  
✔️ MAC destinație  
✔️ MAC sursă  
✔️ EtherType  
✔️ VLAN ID (dacă există)  

---

## 📌 `create_vlan_tag(frame: bytes, vlan_id: int) -> bytes`  
📌 **Adaugă un tag VLAN unui cadru Ethernet**  
✔️ Folosește **0x8200** pentru EtherType VLAN  

---

## 📌 `send_bpdu_every_sec(interfaces: list)`  
📌 **Trimite periodic BPDU-uri pentru STP** (doar dacă switch-ul este root bridge).  
✔️ Construiește și trimite BPDU-uri pe **porturile Trunk**  

---

## 📌 `send_frame(interface: str, frame: bytes)`  
📌 **Trimite un cadru Ethernet pe un port specific**  
✔️ Utilizează `send_to_link()`  

---

## 📌 `load_switch_configuration(switch_id: int)`  
📌 **Încarcă configurația VLAN din fișiere**  
✔️ Setează VLAN-urile pentru porturi  
✔️ Inițializează **stările porturilor** (BLOCKED/DESIGNATED)  

---

# 🔍 Depanare și Debugging
##📌 Analizare pachete cu Wireshark

```bash
wireshark &
```

✔️ Ajută la vizualizarea traficului Ethernet și debugging VLAN/STP.

# 🎯 Concluzie
Această implementare acoperă funcționalitățile de bază ale unui switch Ethernet, incluzând:

✔️ MAC Learning & Forwarding
✔️ VLAN (802.1Q)
✔️ STP (802.1D) pentru evitarea buclelor

Aceasta este o simulare realistă a unui switch în Mininet, folosind Python și interacționând direct cu nivelul Data Link.
