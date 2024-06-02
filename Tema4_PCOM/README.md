# 🖥️ Tema 4: Protocoale de Comunicații

**Lemnaru Mihai-Daniel**  
**Grupa: 322 CD**

---

# 📚 HTTP Client pentru Interacțiune cu un Server REST

Acest proiect reprezintă un client HTTP capabil să comunice cu un server care expune un API de tip REST. S-au implementat funcționalități precum înregistrarea, autentificarea, accesarea bibliotecii, obținerea și gestionarea cărților etc.

### Caracteristici cheie

- 🌐 **HTTP**: Protocol stateless, bazat pe paradigma request/response.
- 🛠️ **Metode HTTP utilizate**:
  - GET: Pentru cereri de citire a unei pagini web.
  - POST: Pentru adăugarea de resurse.
  - DELETE: Pentru ștergerea unei pagini web.
- 🚦 **Coduri de stare HTTP utilizate**:
  - 400: Cerere incorectă.
  - 401: Neautorizat.
  - 403: Interzis.
  - 404: Pagina nu a fost găsită.

### Funcții implementate

1. **register_user**: Înregistrarea unui utilizator în sistem.
2. **login_user**: Autentificarea unui utilizator în sistem.
3. **enter_library**: Solicitarea de acces în bibliotecă.
4. **get_books**: Obținerea listei de cărți din bibliotecă.
5. **get_book**: Obținerea detaliilor unei cărți specifice.
6. **add_book**: Adăugarea unei cărți noi în bibliotecă.
7. **delete_book**: Ștergerea unei cărți din bibliotecă.
8. **logout**: Deconectarea utilizatorului din sistem.

### Structura codului

- **requests.c**: Definiții pentru construirea și trimiterea cererilor HTTP.
  - `compute_get_request`
  - `compute_post_request`
  - `compute_delete_request`
- **client.c**: Implementarea funcțiilor și interacțiunea utilizatorului.
  - Funcții pentru validarea inputului, comunicarea cu serverul și gestionarea răspunsurilor.

### Cum să folosești

Vezi **[Checker.md](Checker.md)**

### Concluzie

Acest client HTTP facilitează interacțiunea cu un server REST, oferind funcționalități esențiale pentru gestionarea unei biblioteci online. Este o bază solidă pentru dezvoltarea ulterioară a unor aplicații mai complexe.

Pentru mai multe detalii, consultați documentația și comentariile în cod.

