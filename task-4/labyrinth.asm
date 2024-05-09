%include "../include/io.mac"

extern printf
extern position
global solve_labyrinth

; you can declare any helper variables in .data or .bss
section .data
	out_line: dd 0
	out_col: dd 0
	m: dd 0
	n: dd 0

	i: dd 0
	j: dd 0

section .text

; void solve_labyrinth(int *out_line, int *out_col, int m, int n, char **labyrinth);
solve_labyrinth:
	;; DO NOT MODIFY
	push    ebp
	mov     ebp, esp
	pusha

	mov     eax, [ebp + 8]  ; unsigned int *out_line, pointer to structure containing exit position
	mov     ebx, [ebp + 12] ; unsigned int *out_col, pointer to structure containing exit position
	mov     ecx, [ebp + 16] ; unsigned int m, number of lines in the labyrinth
	mov     edx, [ebp + 20] ; unsigned int n, number of colons in the labyrinth
	mov     esi, [ebp + 24] ; char **a, matrix represantation of the labyrinth
	;; DO NOT MODIFY
   
	;; Freestyle starts here
	;; Salveaza datele primite ca argumente
	mov [out_line], eax
	mov [out_col], ebx
	mov [m], ecx
	mov [n], edx

	;; Incepe in a[0][0]
	;; ebx contine valoarea de la a[i][j]
	;; ecx contine adresa a[i]
	;; edx contine adresa a[i][j]
	mov dword [i], 0
	mov dword [j], 0
	mov eax, dword [i]
	mov ecx, dword [esi + 4 * eax]
	mov eax, dword [j]
	mov edx, ecx
	add edx, eax

;; Cauta iesirea din labirint
search:
	;; Verifica daca a fost gasita iesirea (i == m - 1 sau j == n - 1)
	mov eax, dword [i]
	mov ebx, dword [m]
	dec ebx
	cmp eax, ebx
	je output
	mov eax, dword [j]
	mov ebx, dword [n]
	dec ebx
	cmp eax, ebx
	je output

check_right:
	;; Verifica daca a[i][j + 1] == '0'
	;; ebx contine adresa a[i][j + 1]
	;; eax contine valoarea de la a[i][j + 1]
	mov eax, dword [i]
	mov ecx, dword [esi + 4 * eax]
	mov eax, dword [j]
	inc eax
	mov ebx, ecx
	add ebx, eax
	movzx eax, byte [ebx]

	cmp eax, 0x30
	jne check_down
	mov byte [edx], 0x31
	inc dword [j]
	mov edx, ebx
	jmp search

check_down:
	;; Verifica daca a[i + 1][j] == '0'
	;; ebx contine adresa a[i + 1][j]
	;; eax contine valoarea de la a[i + 1][j]
	mov eax, dword [i]
	inc eax
	mov ecx, dword [esi + 4 * eax]
	mov eax, dword [j]
	mov ebx, ecx
	add ebx, eax
	movzx eax, byte [ebx]

	cmp eax, 0x30
	jne check_left
	mov byte [edx], 0x31
	inc dword [i]
	mov edx, ebx
	jmp search

check_left:
	;; Verifica daca a[i][j - 1] == '0'
	;; ebx contine adresa a[i][j - 1]
	;; eax contine valoarea de la a[i][j - 1]
	mov eax, dword [i]
	mov ecx, dword [esi + 4 * eax]
	mov eax, dword [j]
	dec eax
	mov ebx, ecx
	add ebx, eax
	movzx eax, byte [ebx]

	cmp eax, 0x30
	jne check_up
	mov byte [edx], 0x31
	dec dword [j]
	mov edx, ebx
	jmp search

check_up:
	;; Verifica daca a[i - 1][j] == '0'
	;; ebx contine adresa a[i - 1][j]
	;; eax contine valoarea de la a[i - 1][j]
	mov eax, dword [i]
	dec eax
	mov ecx, dword [esi + 4 * eax]
	mov eax, dword [j]
	mov ebx, ecx
	add ebx, eax
	movzx eax, byte [ebx]

	cmp eax, 0x30
	jne output
	mov byte [edx], 0x31
	dec dword [i]
	mov edx, ebx
	jmp search

output:
	;; Salveaza coordonatele iesirii
	mov eax, dword [i]
	mov ebx, dword [out_line]
	mov dword [ebx], eax
	mov eax, dword [j]
	mov ebx, dword [out_col]
	mov dword [ebx], eax


	;; Freestyle ends here
end:
	;; DO NOT MODIFY

	popa
	leave
	ret

	;; DO NOT MODIFY
