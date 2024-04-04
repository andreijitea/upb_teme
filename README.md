#### JITEA Andrei-Petru - 315CB
# TEMA SDA 1

## Cuprins
- Proces de realizare a temei
- Continutul arhivei .zip
- Punctaj obtinut cu checker-ul local

## Proces de realizare a temei

Eu am decis in a imparti aceasta tema in 3 task-uri:
- Lista (trenul).
- Coada (comenzile).
- Meniul "interactiv" de a citi comenzile.

Pentru a pastra o lizibilitate a codului am impartit cele 3 task-uri in fisiere sursa separate, pe care le voi prezenta in capitolul urmator.

Lista am implementat-o conform indicatiilor date in cerinta, singura modificare a fost de a adauga o variabila ce retine lungimea momentana a listei, pentru a-mi usura treaba in anumite locuri.

Coada respecta, de asemenea, cerinta temei, dar, precum lista, am folosit si o variabila de lungime a cozii.

Pentru meniul "interactiv", care citeste instructiunile din fisierul de intrare, am hotarat sa asociez fiecarei comenzi, care este salvata in coada, un cod, pentru a le diferentia mai usor.

Deoarece am vrut a da o uniformitate codului, din punct de vedere lingvistic, am intentionat sa scriu cat mai mult in engleza, singurele exceptii fiind comentariile.

Fisierele sursa contin suficiente comentarii pentru a intelege amanuntele rezolvarii acestei teme, asadar nu voi continua in acest README explicatiile codului.



## Continutul arhivei .zip

Arhiva contine urmatoarele fisiere:
- README.md: acest document.
- Makefile: contine cele 3 reguli necesare (build, run, clean), plus inca 3 reguli intermediare celei "build".
- main.c: contine meniul "interactiv" si leaga cele 3 task-uri intr-un tot unitar.
- train_list.c & train_list.h: contin implementarea listei (pentru tren).
- command_queue.c & command_queue.h: contin implementarea cozii (pentru comenzi).


## Punctaj obtinut cu checker-ul local

In urma folosirii checker-ului local, am obtinut urmatorul punctaj:
- Total: 100.0/100
- Valgrind: 20/20