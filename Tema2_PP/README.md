# 🎓 Tema 2 PP 2024: Query Language

## 🛠️ Cerințe Tehnice
- 🖥️ **Scala**: versiunea 3.3.1
- ☕ **JDK**: versiunea 21

## 📚 Cerințe de Stil
- 🔄 Programare funcțională
- 🚫 **NU** se acceptă:
  - ❌ Efecte laterale (ex. modificarea parametrilor dați ca input la funcție)
  - ❌ `var` (doar `val` este ok)

## 🎯 Scopul Temei
Implementarea unui **Query Language** inspirat de SQL, utilizând o bază de date creată de noi.

## 🗂️ Structura Proiectului
### 📝 Reprezentarea Tabelelor
- **Tipuri de date**:
  - `type Row = Map[String, String]` 
  - `type Tabular = List[Row]`
- **Clasa `Table`**:
  - `tableName`: String
  - `tableData`: Tabular

#### Metode în `Table`
1. **📄 toString**: returnează tabelul în format CSV.
2. **➕ insert**: inserează o linie în tabel.
3. **❌ delete**: șterge toate liniile egale cu cea dată ca parametru.
4. **🔄 sort**: sortează liniile din tabel după o anumită coloană.
5. **📊 select**: returnează un nou `Table` conținând doar coloanele specificate.
6. **📝 apply**: parsează un șir de caractere și returnează un tabel cu numele dat.

---

### 🔍 Filtre peste Tabele
- **TDA pentru filtrare**:
  - `Field, Compound, Not, And, Or, Equal, Any, All`

#### ✨ Extensii și Implicite
- **extension**: extinderea clasei FilterCond pentru a adăuga operatori (===, &&, ||, !!).
- **tuple2Field**: implicit pentru conversia tuplurilor în Field.

#### 🛠️ Metode în `Table`
1. **🔍 filter**: filtrează liniile din tabel conform unei condiții.
2. **✏️ update**: actualizează liniile din tabel care respectă o anumită condiție.

---

### 🔄 Operații cu Tabele
- **Clasa** `Database`: conține o listă de tabele.

#### 🛠️ Metode în `Database`
1. **🆕 create**: creează o nouă tabelă.
2. **🗑️ drop**: șterge o tabelă existentă.
3. **📋 selectTables**: extrage un subset de tabele.
4. **🔗 join**: combină două tabele pe baza unei chei comune.

---

### 📜 Query Language
- **TDA** `PP_SQL_DB` și `PP_SQL_Table` pentru operații pe baza de date și tabele.

#### ✨ Operatori Impliciți
- Conversia tuplurilor în query-uri descrise: `PP_SQL_DB_Create_Drop, PP_SQL_DB_Select, PP_SQL_DB_Join, PP_SQL_Table_Insert, PP_SQL_Table_Sort, PP_SQL_Table_Update, PP_SQL_Table_Delete, PP_SQL_Table_Filter, PP_SQL_Table_Select.`

---

### 📝 Query-uri
1. **🗡️ killJackSparrow**: elimină liniile unde valoarea "Jack" apare în coloana "name".
2. **➕🔄 insertLinesThenSort**: inserează o tabelă și apoi sortează după vârstă.
3. **👫 youngAdultHobbiesJ**: combină tabelele `People` și `Hobbies` pe baza coloanelor `name` și filtrează rezultatul.

## 🧪 Testare
Utilizați comanda de mai jos pentru a rula testele:
```sh
sbt test
```
