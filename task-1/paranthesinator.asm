; Interpret as 32 bits code
[bits 32]

%include "../include/io.mac"

section .text
; int check_parantheses(char *str)
global check_parantheses
check_parantheses:
	push ebp
	mov ebp, esp

	;; Salveaza parametrul functiei
	mov edi, [ebp + 8]

loop:
	;; Citeste un caracter din sir
	xor ecx, ecx
	mov cl, [edi]

	;; Verifica tipul de paranteza
	;; Daca este o paranteza deschisa, o pune pe stiva
	;; Daca este o paranteza inchisa, verifica daca se potriveste cu ultima paranteza deschisa
	;; si o scoate de pe stiva
	;; 0x28 - (
	cmp ecx, 0x28
	je l_28
	;; 0x29 - )
	cmp ecx, 0x29
	je l_29
	;; 0x5b - [
	cmp ecx, 0x5b
	je l_5b
	;; 0x5d - ]
	cmp ecx, 0x5d
	je l_5d
	;; 0x7b - {
	cmp ecx, 0x7b
	je l_7b
	;; 0x7d - }
	cmp ecx, 0x7d
	je l_7d
	jmp continue_loop

l_28:
	push ecx
	jmp continue_loop
l_29:
	mov ecx, [esp]
	cmp ecx, 0x28
	jne end_bad
	pop ecx
	jmp continue_loop
l_5b:
	push ecx
	jmp continue_loop
l_5d:
	mov ecx, [esp]
	cmp ecx, 0x5b
	jne end_bad
	pop ecx
	jmp continue_loop
l_7b:
	push ecx
	jmp continue_loop
l_7d:
	mov ecx, [esp]
	cmp ecx, 0x7b
	jne end_bad
	pop ecx
	jmp continue_loop

continue_loop:
	inc edi
	xor ecx, ecx
	mov ecx, [edi]
	cmp ecx, 0x0
	jne loop


end_good:
	;; return 0
	mov eax, 0
	leave
	ret
end_bad:
	;; return 1
	mov eax, 1
	leave
	ret

