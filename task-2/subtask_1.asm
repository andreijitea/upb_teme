; subtask 1 - qsort

section .text
	global quick_sort
	;; no extern functions allowed

quick_sort:
	;; create the new stack frame
	enter 0, 0

	;; Unde sunt salvate argumentele
	;; [ebp + 8] - buffer
	;; [ebp + 12] - start
	;; [ebp + 16] - end
	;; [ebp - 4] - pivot
	sub esp, 4
	;; [ebp + 12] - start
	mov eax, [ebp + 12]
	;; [ebp + 16] - end
	cmp eax, dword [ebp + 16]
	jge end
	jmp partition

partition:
	;; Calculeaza pivotul
	push ebx
	;; [ebp + 16] - end
	mov eax, [ebp + 16]
	;; [ebp + 8] - buffer
	mov ebx, [ebp + 8]
	;; [ebx + eax * 4] - buffer[end]
	mov ebx, [ebx + eax * 4]
	;; [ebp - 4] - pivot
	mov dword [ebp - 4], ebx
	pop ebx
	;; i - ecx
	;; j - edx
	;; [ebp + 12] - start
	mov ecx, [ebp + 12]
	dec ecx
	;; [ebp + 12] - start
	mov edx, [ebp + 12]
for_j:
	;; [ebp + 8] - buffer
	mov eax, [ebp + 8]
	;; [eax + edx * 4] - buffer[j]
	mov eax, [eax + edx * 4]
	;; [ebp - 4] - pivot
	cmp eax, dword [ebp - 4]
	jge inc_for_j
	;; Swap intre buff[i] si buff[j]
	inc ecx
	push ebx
	;; buff[i]
	;; [ebp + 8] - buffer
	mov eax, [ebp + 8]
	;; [eax + ecx * 4] - buffer[i]
	mov eax, [eax + ecx * 4]
	push eax
	;; buff[j]
	;; [ebp + 8] - buffer
	mov eax, [ebp + 8]
	;; [eax + edx * 4] - buffer[j]
	mov eax, [eax + edx * 4]
	push eax
	;; Swap
	pop eax
	;; [ebp + 8] - buffer
	mov ebx, [ebp + 8]
	;; [ebx + ecx * 4] - buffer[i]
	mov [ebx + ecx * 4], eax
	pop eax
	;; [ebp + 8] - buffer
	mov ebx, [ebp + 8]
	;; [ebx + edx * 4] - buffer[j]
	mov [ebx + edx * 4], eax
	pop ebx
	;; Incrementeaza for_j
inc_for_j:
	inc edx
	;; [ebp + 16] - end
	cmp edx, dword [ebp + 16]
	jl for_j
end_partition:
	;; Swap intre buff[i + 1] si buff[end]
	push ebx
	inc ecx
	;; buff[i + 1]
	;; [ebp + 8] - buffer
	mov eax, [ebp + 8]
	;; [eax + ecx * 4] - buffer[i + 1]
	mov eax, [eax + ecx * 4]
	push eax
	;; buff[end]
	;; [ebp + 16] - end
	mov edi, [ebp + 16]
	;; [ebp + 8] - buffer
	mov eax, [ebp + 8]
	;; [eax + edi * 4] - buffer[end]
	mov eax, [eax + edi * 4]
	push eax
	;; Swap
	pop eax
	;; [ebp + 8] - buffer
	mov ebx, [ebp + 8]
	;; [ebx + ecx * 4] - buffer[i + 1]
	mov [ebx + ecx * 4], eax
	pop eax
	;; [ebp + 8] - buffer
	mov ebx, [ebp + 8]
	;; [ebx + edi * 4] - buffer[end]
	mov [ebx + edi * 4], eax
	pop ebx
	;; Actualizeaza pivotul
	;; [ebp - 4] - pivot
	mov [ebp - 4], ecx

continue_qsort:
	;; Sorteaza recursiv partea stanga
	;; [ebp - 4] - pivot
	mov ecx, [ebp - 4]
	dec ecx
	push ecx
	;; [ebp + 12] - start
	push dword [ebp + 12]
	;; [ebp + 8] - buffer
	push dword [ebp + 8]
	call quick_sort
	;; 16 = 4 valori de 4 octeti pe stiva
	add esp, 16

	;; Sorteaza recursiv partea dreapta
	add ecx, 1
	;; [ebp + 16] - end
	push dword [ebp + 16]
	push ecx
	;; [ebp + 8] - buffer
	push dword [ebp + 8]
	call quick_sort
	;; 16 = 4 valori de 4 octeti pe stiva
	add esp, 16

end:
	leave
	ret
