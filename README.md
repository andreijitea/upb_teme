#### Jitea Andrei-Petru - 315CB

# Metode Numerice - Tema 2

## Cuprins
- Proces de realizare a temei
- Continutul arhivei .zip
- Punctaj obtinut cu checker-ul local

## Proces de realizare a temei

### 1. Task 1 - Numerical Music:
In cadrul acestui task am implementat urmatoarele functii:
- `apply_reverb` - functie care adauga un efect de reverb pe un semnal audio
- `low_pass` - functie care aplica un filtru low-pass pe un semnal audio
- `oscillator` - functie care genereaza un semnal audio de tip sinusoidal
- `spectogram` - functie care genereaza o spectograma a unui semnal audio
- `stereo_to_mono` - functie care transforma un semnal audio stereo intr-unul mono

In continuare, voi prezenta rezultatele obtinute la rularea `studio.m`:
- Diferenta dintre spectograma Plain Sound si cea Plain Loop este reprezentata de faptul ca Plain Loop este un semnal audio continuu, in timp ce Plain Sound este un semnal audio discontinuu, fiind generat de un pattern din cadrul fisierului `music1.csv`.
- Diferenta dintre spectograma Low Pass Sound si cea Plain Sound este reprezentata de faptul ca Low Pass Sound este semnalul audio Plain Sound la care i s-a aplicat un filtru low-pass, tip de filtru care ateunueaza frecventele inalte.
- Diferenta dintre spectograma Reverb Sound si cea Plain Sound este reprezentata de faptul ca Reverb Sound este semnalul audio Plain Sound la care i s-a adaugat un efect de reverb, efect care simuleaza ecoul. Astfel, semnalul nu se mai opreste brusc, ci se stinge treptat.
- Spectograma Tech reprezinta un semnal audio fara efecte.
- Spectograma Low Pass Tech reprezinta semnalul audio Tech la care i s-a aplicat un filtru low-pass.
- Spectograma Reverb Tech reprezinta semnalul audio Tech la care i s-a adaugat un efect de reverb.
- Spectograma Low Pass + Reverb Tech reprezinta semnalul audio Tech la care i s-au aplicat mai intai un filtru low-pass, iar apoi un efect de reverb.
- Spectograma Reverb + Low Pass Tech reprezinta semnalul audio Tech la care i s-a adaugat mai intai un efect de reverb, iar apoi un filtru low-pass. **Aceasta spectograma este diferita de cea anterioara, deoarece ordinea in care se aplica efectele influenteaza semnalul audio rezultat.**

### 2. Task 2 - Robotzii:
In cadrul acestui task am implementat 2 tipuri de interpolari: Vandermonde si Cubic Spline, in cadrul urmatoarelor functii:
- `parse_data` - functie care citeste datele din fisierul de intrare si le salveaza in 2 vectori: x si y
- `vandermonde` - functie care realizeaza interpolarea Vandermonde
- `p_vandermonde` - functie care calculeaza polinomul de interpolare Vandermonde
- `spline_c2` - functie care realizeaza interpolarea Cubic Spline
- `p_spline` - functie care calculeaza polinomul de interpolare Cubic Spline

Pentru aceste functii, am urmat pasii din enuntul temei.


### 3. Task 3 - Recommendations:
Pentru acest task am implementat urmatoarele functii:
- `read_mat` - functie care citeste dintr-un fisier `.csv` si salveaza datele intr-o matrice
- `preprocess` - functie care elimina linile care nu indeplinesc o conditie data
- `cosine_similarity` - functie care calculeaza similaritatea dintre 2 vectori, folosind cosinusul dintre acestia
- `recommendations` - functie care calculeaza indicii temelor recomandate, folosind functile de mai sus si algoritmul SVD

## Continutul arhivei .zip
- `README.md` - fisierul curent
- `numerical_music/` - directorul care contine implementarea task-ului 1
- `robotzii/` - directorul care contine implementarea task-ului 2
- `recommendations/` - directorul care contine implementarea task-ului 3

## Punctaj obtinut cu checker-ul local
- Task 1: 26p / 30p
- Task 2: 26p / 30p
- Task 3: 30p / 30p
- Total: 82p / 90p