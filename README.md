#### Jitea Andrei-Petru - 315CB

# Tema 3 - Suricate in retea

## Cuprins
1. [Proces de realizare a temei](#proces-de-realizare-a-temei)
2. [Continutul arhivei .zip](#continutul-arhivei-zip)
3. [Punctaj obtinut local](#punctaj-obtinut-local)

## Proces de realizare a temei
Pentru aceasta tema am reusit sa rezolv task-urile 1, 2 si bonusul.
### Task 1
Pentru primul task am implementat functia `check_parantheses()` din fisierul `paranthesinator.asm`

Pentru a verifica daca un sir contine perechi de paranteze corecte am folosit stiva in urmatorul fel:
- Daca caracterul curent este unul din caracterele deschise, il adaug pe stiva
- Daca caracterul curent este unul din caracterele inchise, verific daca ultimul caracter adaugat pe stiva este caracterul deschis corespunzator:
  - Daca este, elimin caracterul de pe stiva.
  - Daca nu este, inseamna ca sirul nu contine perechi de paranteze corecte si returnez 1.
  - Daca stiva este goala la final, inseamna ca sirul contine perechi de paranteze corecte si returnez 0.

### Task 2
Pentru acest task am implementat urmatoarele functii:
1. `quick_sort`, din fisierul `subtask_1.asm`
2. `binary_search`, din fisierul `subtask_2.asm`
### Quick Sort
Pentru a implementa acest algoritm am folosit o functie auxiliara `partition` care imparte vectorul in doua parti, una cu elemente mai mici decat pivotul si una cu elemente mai mari decat pivotul.

Aceasta functie este incorporata in functia `quick_sort`, folosind un label.

Pentru a face swap intre 2 elemente am folosit stiva.

### Binary Search
Aceasta functie are salvati primii 2 parametri in registrele `ecx` si `edx`, iar restul parametrilor sunt salvati pe stiva.

#### Ambele functii sunt rezolvate folosind metode recursive.

#### Pentru recursivitate, toate variabilele necesare sunt salvate pe stiva.

### Task bonus
Pentru ultimul task am implementat cele 2 functii elementare programarii functionale: `map` si `filter`, din fisierul `functional.asm`.

Pentru a le rezolva, am urmat pseudocodul din enuntul temei.

## Continutul arhivei .zip
- README.md
- paranthesinator.asm - rezolvarea task-ului 1
- subtask_1.asm - rezolvarea task-ului 2, subtask-ul 1
- subtask_2.asm - rezolvarea task-ului 2, subtask-ul 2
- task_3.asm
- functional.asm - rezolvarea task-ului bonus

## Punctaj obtinut local
- Task 1: 30p
- Task 2: 30p
- Task 3: 0p
- Bonus: 30p