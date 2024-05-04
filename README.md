### JITEA Andrei-Petru - 315CB

# Tema 2 SDA - Arbori de sufixe

## Cuprins
1. [Proces de realizare a temei](#proces-de-realizare-a-temei)
2. [Continutul arhivei .zip](#continutul-arhivei-zip)
3. [Punctaj obtinut cu checker-ul local](#punctaj-obtinut-cu-checker-ul-local)


## Proces de realizare a temei
Pentru aceasta tema am rezolvat primele 3 cerinte.
### Cerinta 1:
Rezolvarea primei cerinte consta in functia `task1` din fisierul `tasks_helpers.c`.  
In cadrul acestei functii, sunt apelate alte 2 functii ajutatoare:
- `makeTree` - construieste arborele de sufixe pentru un numar de cuvinte.  
Aceasta functie foloseste la randul ei functia `addSuffix` pentru a adauga fiecare sufix al unui cuvant in arbore.
- `printTree` - afiseaza in latime arborele de sufixe construit.  
Aceasta functie afiseaza recursiv arborele, incepand de la nivelul 1 (ignorand radacina arborelui) in felul urmator:
  - Calculeaza inaltimea arborelui, folosind functia `getTreeHeight`
  - Itereaza peste fiecare nivel al arborelui functia `printTreeLevel`.  
  Aceasta functie parcurge arborele de la radacina pana ajunge la nivelul dorit si afiseaza nodurile.
### Cerinta 2:
Rezolvarea acestie cerinte consta in functia `task2` din fisierul `tasks_helpers.c`.
In cadrul acestei functii, sunt apelate alte 4 functii ajutatoare:
- `makeTree` - construieste arborele de sufixe pentru un numar de cuvinte.
- `countLeaves` - numara frunzele arborelui de sufixe.
- `countKLenSuffixes` - numara sufixele de lungime k din arborele de sufixe.  
Mentionez ca aceasta functie foloseste lungimea `k + 1`, deoarece ia in considerare si caracterul special `'$'` adaugat la finalul fiecarui sufix.
- `maxChildren` - calculeaza numarul maxim de descendenti directi pe care ii are un nod din arborele de sufixe.
### Cerinta 3:
Rezolvarea acestei cerinte consta in functia `task3` din fisierul `tasks_helpers.c`.  
In cadrul acestei functii, sunt apelate alte 2 functii ajutatoare:
- `makeTree` - construieste arborele de sufixe pentru un numar de cuvinte.
- `findSuffix` - cauta un sufix in arborele de sufixe.
---
*Mentionez ca fisierele sursa contin un numar mare de comentarii, care sper sa lamureasca orice detaliu legat de implementare, pe care nu l-am prezentat in mai sus.*

## Continutul arhivei .zip
Arhiva .zip contine urmatoarele fisiere:
- `Makefile` - fisierul de compilare, contine comenzile `build` si `clean`, conform cerintei.
- `README.md` - fisierul curent.
- `tree.c` si `tree.h` - contin implementarea arborelui simplu de sufixe (nu cel compact) si a functiilor necesare pentru a-l construi si a-l afisa.
- `tasks_helpers.c` si `tasks_helpers.h` - contin implementarea functiilor ajutatoare pentru rezolvarea primelor 3 cerinte.
- `main.c` - apeleaza functiile `task1`, `task2` si `task3`, in functia parametrilor primiti de la linia de comanda.

## Punctaj obtinut cu checker-ul local
In urma rularii checker-ului local, am obtinut urmatorul punctaj:  
- Cerinta 1 : 30  
- Cerinta 2 : 20  
- Cerinta 3 : 20  
- Cerinta 4 : 0  
- Total : 70  
- Bonus : 15.0

