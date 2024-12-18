section .rodata
	global sbox
	global num_rounds
	sbox db 126, 3, 45, 32, 174, 104, 173, 250, 46, 141, 209, 96, 230, 155, 197, 56, 19, 88, 50, 137, 229, 38, 16, 76, 37, 89, 55, 51, 165, 213, 66, 225, 118, 58, 142, 184, 148, 102, 217, 119, 249, 133, 105, 99, 161, 160, 190, 208, 172, 131, 219, 181, 248, 242, 93, 18, 112, 150, 186, 90, 81, 82, 215, 83, 21, 162, 144, 24, 117, 17, 14, 10, 156, 63, 238, 54, 188, 77, 169, 49, 147, 218, 177, 239, 143, 92, 101, 187, 221, 247, 140, 108, 94, 211, 252, 36, 75, 103, 5, 65, 251, 115, 246, 200, 125, 13, 48, 62, 107, 171, 205, 124, 199, 214, 224, 22, 27, 210, 179, 132, 201, 28, 236, 41, 243, 233, 60, 39, 183, 127, 203, 153, 255, 222, 85, 35, 30, 151, 130, 78, 109, 253, 64, 34, 220, 240, 159, 170, 86, 91, 212, 52, 1, 180, 11, 228, 15, 157, 226, 84, 114, 2, 231, 106, 8, 43, 23, 68, 164, 12, 232, 204, 6, 198, 33, 152, 227, 136, 29, 4, 121, 139, 59, 31, 25, 53, 73, 175, 178, 110, 193, 216, 95, 245, 61, 97, 71, 158, 9, 72, 194, 196, 189, 195, 44, 129, 154, 168, 116, 135, 7, 69, 120, 166, 20, 244, 192, 235, 223, 128, 98, 146, 47, 134, 234, 100, 237, 74, 138, 206, 149, 26, 40, 113, 111, 79, 145, 42, 191, 87, 254, 163, 167, 207, 185, 67, 57, 202, 123, 182, 176, 70, 241, 80, 122, 0
	num_rounds dd 10

section .data
	round dd 0
	i db 0


section .text
	global treyfer_crypt
	global treyfer_dcrypt

; void treyfer_crypt(char text[8], char key[8]);
treyfer_crypt:
	;; DO NOT MODIFY
	push ebp
	mov ebp, esp
	pusha

	mov esi, [ebp + 8] ; plaintext
	mov edi, [ebp + 12] ; key	
	;; DO NOT MODIFY
	;; FREESTYLE STARTS HERE
	;; Se considera t == bl
	;; Seteaza t cu primul caracter din text
	mov bl, [esi]
	;; Reseteaza counter-ul de runde
	mov dword [round], 0
cr_for_round:
	;; Reseteaza i
	mov byte [i], 0
cr_for_i:
	;; Aduna la t (bl) caracterul de pe pozitia i din key
	movzx eax, byte [i]
	add bl, [edi + eax]

	;; Substituie t (bl) cu valoarea din sbox corespunzatoare lui t (bl)
	movzx eax, bl
	mov bl, [sbox + eax]

	;; Aduna la t (bl) caracterul de pe pozitia i+1 din text (daca i+1 == 8, atunci i+1 == 0)
	;; folosind (i + 1) % 8, rezultatul se gaseste in edx
	movzx eax, byte [i]
	inc eax
	mov ecx, 8
	xor edx, edx
	div ecx
	add bl, [esi + edx]

	;; Roteste la stanga t (bl) cu 1 bit
	rol bl, 1

	;; Byte-ul de pe poziția (i + 1) % 8 din text va fi actualizat cu valoarea variabilei t (bl)
	;; folosind (i + 1) % 8, rezultatul se gaseste in edx
	movzx eax, byte [i]
	inc eax
	mov ecx, 8
	xor edx, edx
	div ecx
	mov byte [esi + edx], bl

	;; Itereaza for_i
	inc byte [i]
	cmp byte [i], 8
	jl cr_for_i

continue_cr_for_round:
	;; Itereaza for_round
	inc dword [round]
	mov eax, [num_rounds]
	cmp [round], eax
	jl cr_for_round

end_treyfer_crypt:
	;; FREESTYLE ENDS HERE
	;; DO NOT MODIFY
	popa
	leave
	ret

; void treyfer_dcrypt(char text[8], char key[8]);
treyfer_dcrypt:
	;; DO NOT MODIFY
	push ebp
	mov ebp, esp
	pusha
	;; DO NOT MODIFY
	;; FREESTYLE STARTS HERE
	;; Salveaza adresele textului si cheii
	mov esi, [ebp + 8] ; encrypted text
	mov edi, [ebp + 12] ; key

	;; Reseteaza counter-ul de runde
	mov dword [round], 0
	;; Se considera bh = top si bl = bottom

dcr_for_round:
	;; Reseteaza i
	mov byte [i], 7
dcr_for_i:
	xor bx, bx
	;; Aduna la top (bh) caracterul de pe pozitia i din key si din text
	movzx eax, byte [i]
	add bh, [edi + eax]
	add bh, [esi + eax]

	;; Substituie top (bh) cu valoarea din sbox corespunzatoare lui top (bh)
	movzx eax, bh
	mov bh, [sbox + eax]

	;; Muta caracterul de pe pozitia (i + 1) % 8 din text in bottom (bl)
	;; folosind (i + 1) % 8, rezultatul se gaseste in edx
	movzx eax, byte [i]
	inc eax
	mov ecx, 8
	xor edx, edx
	div ecx
	mov bl, [esi + edx]

	;; Roteste la dreapta bottom (bl) cu 1 bit
	ror bl, 1

	;; Byte-ul de pe poziția (i + 1) % 8 din text va fi actualizat cu diferenta bottom (bl) - top (bh)
	;; folosind (i + 1) % 8, rezultatul se gaseste in edx
	movzx eax, byte [i]
	inc eax
	mov ecx, 8
	xor edx, edx
	div ecx
	sub bl, bh
	mov byte [esi + edx], bl

	;; Itereaza for_i
	dec byte [i]
	cmp byte [i], 0
	jge dcr_for_i

continue_dcr_for_round:
	;; Itereaza for_round
	inc dword [round]
	mov eax, [num_rounds]
	cmp [round], eax
	jl dcr_for_round

end_treyfer_dcrypt:
	;; FREESTYLE ENDS HERE
	;; DO NOT MODIFY
	popa
	leave
	ret

