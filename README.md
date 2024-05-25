### JITEA Andrei-Petru - 315CB

# Tema 3 SDA - Grafuri

## Cuprins
1. [Proces de realizare a temei](#proces-de-realizare-a-temei)
2. [Continutul arhivei .zip](#continutul-arhivei-zip)
3. [Punctaj obtinut cu checker-ul local](#punctaj-obtinut-cu-checker-ul-local)


## Proces de realizare a temei
### 1. Cerinta 1
Pentru a rezolva prima cerinta, am implementat in fisierele `task1.c` si `task1.h` urmatoarele:
- structura `GraphCity` - graful care contine informatii despre orase si tronsoanele unei muchii
- structura `GraphTr` - graful care contine fiecare tronson din grafca un nod
- functii pentru initializarea si eliberarea memoriei pentru cele 2 structuri
- functii pentru citirea si scrierea grafului de orasein/din fisier
- functia `ageGraph` - aplica procesul de degradare a tronsoanelor din graf

### 2. Cerinta 2
Pentru a rezolva aceasta cerinta, am implementat in fisierele `task2.c` si `task2.h` urmatoarele:
- structura `GraphCity2` - graful care contine informatii despre orase
- functii pentru initializarea si eliberarea memoriei pentru structura
- functii pentru citirea si scrierea grafului de orase in/din fisier
- functia `setCityIds` - seteaza id-urile oraselor in graf, pentru a aplica algoritmul Dijkstra
- functia `dijkstra`:
  - implementarea algoritmului Dijkstra pentru a gasi drumul minim intre 2 orase
  - functia decide care muchii sunt necesare parcurgerii grafului si le seteaza un status, `USED` sau `UNUSED`

---
#### In cadrul fisierelor sursa am folosit foarte multe comentarii, care detaliaza fiecare pas al implementarii, pentru a usura intelegerea codului.

---
## Continutul arhivei .zip
Arhiva .zip contine urmatoarele fisiere:
- `Makefile` - fisierul de compilare, contine comenzile `build` si `clean`, conform cerintei.
- `README.md` - fisierul curent.
- `task1.c` & `task1.h` - fisierul sursa si header-ul pentru rezolvarea cerintei 1.
- `task2.c` & `task2.h` - fisierul sursa si header-ul pentru rezolvarea cerintei 2.
- `main.c` - fisierul principal, care contine rezolvarile celor 2 cerinte.

## Punctaj obtinut cu checker-ul local
In urma rularii checker-ului local, am obtinut urmatorul punctaj:
- Task 1: 45.0/45p
- Task 2: 35.0/50p
- README: 5.0/5p
- Bonus Valgrind: 17.0/20p
- Total: 102.0/120p