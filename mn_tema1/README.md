#### Jitea Andrei-Petru - 315CB
# MN - Tema de casa 1 - Analiza datelor

## Cuprins
- Proces de realizare a temei.
- Continutul arhivei .zip.
- Punctaj obtinut cu checker-ul local.

## Proces de realizare a temei

Am rezolvat totul, mai putin matricea stocastica, din cadrul taskul-ui 3. Am incercat sa folosesc cat mai multe comentarii in fisierele sursa, explicand functionalitatea fiecarei functii. Majoritatea au fost implementate conform formulelor/indicatiilor date in PDF, asadar nu le voi prezenta in acest document. In schimb, voi explica in detaliu cele 2 functii pe care a trebuit sa le implementam independent: **cholesky()** si **get_lower_inverse()**.

In cadrul functiei **get_lower_inverse()** am implementat algoritmul Gauss-Jordan de obtinere a inversei unei matrice (A | eye) -> (eye | A^-1), algoritm pe jumatate facut de la bun inceput, deoarece A este o matrice inferior triunghiulara.

$$\begin{bmatrix}A | I_{n}\end{bmatrix} \rightarrow \begin{bmatrix}I_{n} | A^{-1}\end{bmatrix}$$

Pentru **cholesky()** am implementat o metoda alternativa de rezolvare, tratand matricea A in urmatorul fel:
$$A = L * L^T$$
$$A = \begin{bmatrix}a_{11} & A_{21}^T\\
A_{21} & A_{22}\\
\end{bmatrix}$$
$$L = \begin{bmatrix}l_{11} & 0\\
L_{21} & L_{22}\\
\end{bmatrix}$$
De unde rezulta:
$$l_{11} = \sqrt{a_{11}}$$
$$L_{21} = A_{21} / l_{11}$$
$$L_{22} * L_{22}^T = A_{22} - L_{21} * L_{21}^T$$
Astfel, consider minorul lui A
$$A_{22} = L_{22} * L_{22}^T$$
Si algoritmul continua pentru minorul lui A...

## Continutul arhivei .zip

Conform cerintei, arhiva contine doar cele 3 directoare, ce contin fisierele sursa (anomaly_detection, kernel_regression si stochastic_text_generation), impreuna cu acest fisier README.md.

## Punctaj obtinut cu checker-ul local

Folosind checker-ul local am obtinut urmatorul punctaj:
- Task 1: 20p / 20p.
- Task 2: 35.0p / 35.0p.
- Task 3: 24p / 45p.
- Final score: 79.0p / 100.0p.