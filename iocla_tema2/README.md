#### Jitea Andrei-Petru - 315CB

# Tema 2 - Intrusion Detection with Suricata

## Cuprins
1. [Proces de realizare a temei](#proces-de-realizare-a-temei)
2. [Continutul arhivei .zip](#continutul-arhivei-zip)
3. [Punctaj obtinut local](#punctaj-obtinut-local)


## Proces de realizare a temei
Din aceasta tema am reusit sa rezolv task-urile 1, 3 si 4.

#### 1. Task 1 - Permissions:
In cadrul acestui task am implementat functia `check_permission` in fisierul `check_permission.asm` in urmatorul mod:
- Am calculat id-ul furnicii.
- Am calculat lista de sali dorite de furnica.
- Am comparat lista de sali dorite cu cea de sali permise.
- Functia returneaza 1 daca furnica are acces la toate salile dorite, 0 altfel.

#### 2. Task 3 - Treyfer:
Pentru acest task am implementat cele 2 functii cerute in fisierul `treyfer.asm`, urmarind echivalentul lor din C.

Aceste implementari le-am gasit pe pagina de Wikipedia a algoritmului Treyfer, dat in enuntul temei.
1. Functia `treyfer_crypt`:
    - Este alcatuita din 2 loop-uri, unul exterior pentru numarul de runde, iar celalalt interior pentru fiecare element din blocul de date.
    - In cadrul loop-ului interior, se prelucreaza fiecare element din blocul de date, conform etapelor prezentate in enunt.
    - Pentru a obtine `(i + 1) % block_size` am procedat astfel:
        - Am salvat in registrul `EAX` valoarea `i + 1`.
        - Am salvat in registrul `ECX` valoarea `block_size`.
        - Am folosit instructiunea `div` pentru a calcula restul impartirii lui `EAX` la `ECX`.
        - Restul impartirii este salvat in registrul `EDX`.
2. Functia `treyfer_dcrypt`:
    - Este alcatuita din 2 loop-uri, unul exterior pentru numarul de runde, iar celalalt interior pentru fiecare element din blocul de date.
    - In cadrul loop-ului interior, se prelucreaza fiecare element din blocul de date, conform etapelor prezentate in enunt.
    - Pentru a obtine `(i + 1) % block_size` am procedat ca in cazul functiei `treyfer_crypt`.

#### 3. Task 4 - Labyrinth:
Pentru acest task am implementat functia `labyrinth` in fisierul `labyrinth.asm` in urmatorul mod:
- Am folosit un loop `search` in cadrul careia este parcurs labirintul pana la gasirea iesirii.
- In interiorul acestui loop am implementat 4 cazuri pentru fiecare directie in care se poate deplasa.
- Daca a fost gasit urmatorul pas, se intampla urmatoarele:
    - Se actualizeaza coordonatele x, y (i, j).
    - Elementul curent devine `1`, pentru a nu se mai intoarce in acelasi loc.
    - Se actualizeaza adresa de memorie a elementului curent, cu adresa elementului urmator.
- Dupa ce a fost gasita iesirea, se salveaza valorile x, y (i, j) in adresele date ca parametrii.

## Continutul arhivei .zip
In arhiva .zip se regasesc urmatoarele fisiere:
- task-1/check_permission.asm
- task-2/subtask1.asm
- task-2/subtask2.asm
- task-3/treyfer.asm
- task-4/labyrinth.asm
- README.md

## Punctaj obtinut local
- Task 1: 15.00 / 15.00
- Task 2: 0.00 / 20.00
- Task 3: 25.00 / 25.00
- Task 4: 30.00 / 30.00
- Total: 70.00 / 100.00
