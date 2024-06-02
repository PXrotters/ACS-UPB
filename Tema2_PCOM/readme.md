# 🖥️ Tema 2: Protocoale de Comunicații

**Lemnaru Mihai-Daniel**  
**Grupa: 322 CD**

---

## ℹ️ Descriere
Acest proiect este un sistem de comunicare client-server care permite transmiterea de mesaje între clienți și server utilizând protocolul UDP și TCP.

---

## 🔧 Componente

### Comunicarea de la client la server:
- Transmiterea ID-ului clientului la conectare: Clientul trimite ID-ul său la conectare pentru a identifica și autentifica conexiunea către server.
- Emisia comenzii de abonare (subscribe) la un anumit topic: Clientul emite o comandă de abonare pentru a se abona la actualizările unui anumit topic de interes.
- Emisia comenzii de dezabonare (unsubscribe) de la un topic: Clientul emite o comandă de dezabonare pentru a se dezabona de la actualizările unui topic la care este deja abonat.

### Comunicarea de la server la client:
- Transmiterea actualizărilor topic-urilor abonate: Serverul informează clientul despre orice actualizări sau evenimente legate de topic-urile la care clientul este abonat, permitându-i să primească și să proceseze informațiile relevante.

---

## 🛠️ Structuri și Funcții

### helpers.h:
- `struct udp_message`: Structura definită prin care serverul primește mesaje de la UDP.
- `struct subscriber_message`: Structura prin care serverul primește mesaje de la clientul TCP. Conține comanda primită de subscribe/unsubscribe, topic-ul la care face referire, respectiv dacă vrea sau nu să activeze opțiunea sf.
- `struct server_message`: Structura care ajută serverul să trimită mesaje către clientul TCP. Conține lungimea mesajului trimis, adresa, topicul la care face referire mesajul și tipul de date pe care îl trimite.
- `struct subscriber`: Structura care salvează datele abonaților. Conține ID-ul fiecăruia, socketul, conectivitatea acestuia, 2 vectori care rețin topic-ul la care e abonat subscriber-ul respectiv, dacă el are flag-ul setat și numărul de topicuri pe care le reține el în subscripție.

### server.c:
- `findSubscriberByClientId`: Funcție care caută un abonat într-un tablou de structuri de abonat, pe baza ID-ului sau de client.
- `findTextByInfo`: Funcție care caută un text într-un tablou bidimensional de caractere, pe baza unei informații date.
- `findSubscribers`: Funcție care caută un abonat într-un tablou de structuri de abonat, pe baza descriptorului de fișier al socket-ului sau.
- `prepareServerForComm`: Funcție care pregătește serverul pentru a primi conexiuni TCP și UDP pe un anumit port.
- `handleExitCommand`: Funcție care gestionează comanda de ieșire primită de la client.
- `handleUdpMessage`: Funcție care primește un mesaj UDP și îl procesează pentru a-l trimite către abonații interesați.
- `handleUdp`: Funcție care primește mesaje UDP de la clienți și le gestionează utilizând funcția `handleUdpMessage`.
- `handleTcpConnection`: Funcție care primește o conexiune TCP nouă și gestionează conectarea clientului asociat.
- `handleSubscriberMessage`: Funcție care primește un mesaj de la un abonat și actualizează lista de abonamente a abonatului în funcție de comanda primită (subscribe/unsubscribe).
- `main`: Funcție principală care inițializează și gestionează funcțiile serverului.

### subscriber.c:
- Funcții pentru afișarea diferitelor tipuri de date și mesaje.
- `establishTcpConnWithServer`: Funcție care configurează și stabilește conexiunea TCP cu serverul.
- `handleSubscriptionsAndMessages`: Funcție care gestionează abonamentele și mesajele cu serverul.
- `main`: Funcție principală care inițializează și gestionează funcțiile clientului.

---

✍️ **Documentația este realizată pentru a facilita înțelegerea și utilizarea funcțiilor descrise.**
