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

    mov eax, [ebp + 12]
    cmp eax, dword [ebp + 16]
    jge end
    jmp partition

partition:
    ;; Calculeaza pivotul
    push ebx
    mov eax, [ebp + 16]
    mov ebx, [ebp + 8]
    mov ebx, [ebx + eax * 4]
    mov dword [ebp - 4], ebx
    pop ebx
    ;; i - ecx
    ;; j - edx
    mov ecx, [ebp + 12]
    dec ecx
    mov edx, [ebp + 12]
for_j:
    mov eax, [ebp + 8]
    mov eax, [eax + edx * 4]
    cmp eax, dword [ebp - 4]
    jge inc_for_j
    ;; Swap intre buff[i] si buff[j]
    inc ecx
    push ebx
    ;; buff[i]
    mov eax, [ebp + 8]
    mov eax, [eax + ecx * 4]
    push eax
    ;; buff[j]
    mov eax, [ebp + 8]
    mov eax, [eax + edx * 4]
    push eax
    ;; Swap
    pop eax
    mov ebx, [ebp + 8]
    mov [ebx + ecx * 4], eax
    pop eax
    mov ebx, [ebp + 8]
    mov [ebx + edx * 4], eax
    pop ebx
    ;; Incrementeaza for_j
inc_for_j:
    inc edx
    cmp edx, dword [ebp + 16]
    jl for_j
end_partition:
    ;; Swap intre buff[i + 1] si buff[end]
    push ebx
    inc ecx
    ;; buff[i + 1]
    mov eax, [ebp + 8]
    mov eax, [eax + ecx * 4]
    push eax
    ;; buff[end]
    mov edi, [ebp + 16]
    mov eax, [ebp + 8]
    mov eax, [eax + edi * 4]
    push eax
    ;; Swap
    pop eax
    mov ebx, [ebp + 8]
    mov [ebx + ecx * 4], eax
    pop eax
    mov ebx, [ebp + 8]
    mov [ebx + edi * 4], eax
    pop ebx
    ;; Actualizeaza pivotul
    mov [ebp - 4], ecx

continue_qsort:
    ;; Sorteaza recursiv partea stanga
    mov ecx, [ebp - 4]
    dec ecx
    push ecx
    push dword [ebp + 12]
    push dword [ebp + 8]
    call quick_sort
    add esp, 16

    ;; Sorteaza recursiv partea dreapta
    add ecx, 1
    push dword [ebp + 16]
    push ecx
    push dword [ebp + 8]
    call quick_sort
    add esp, 16

end:
    leave
    ret
