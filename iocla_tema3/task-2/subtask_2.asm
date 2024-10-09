; subtask 2 - bsearch

section .text
    global binary_search
    ;; no extern functions allowed

binary_search:
    ;; create the new stack frame
    enter 0, 0

    ;; Unde sunt salvate argumentele
    ;; [ebp + 8] - start
    ;; [ebp + 12] - end
    ;; ecx - buffer
    ;; edx - needle
    ;; [ebp - 4] - mid
    sub esp, 4
    ;; [ebp - 4] - mid
    mov dword [esp - 4], 0
    ;; [ebp + 12] - end
    mov eax, [ebp + 12]
    ;; [ebp + 8] - start
    cmp eax, dword [ebp + 8]
    jl ret_neg
    ;; Calculeaza mijlocul listei
    add eax, dword [ebp + 8]
    ;; impartirea la 2
    sar eax, 1
    ;; [ebp - 4] - mid
    mov [ebp - 4], eax
    ;; Verifica daca elementul de la mijloc este acelasi cu acela cautat
    cmp edx, [ecx + eax * 4]
    jne not_equal
    jmp end
not_equal:
    ;; Verifica daca elementul de la mijloc este mai mare decat cel cautat
    ;; start = start, end = mid - 1
    cmp edx, [ecx + eax * 4]
    jg not_greater
    ;; [ebp + 12] - end
    sub dword [ebp + 12], 1
    ;; [ebp + 12] - end
    push dword [ebp + 12]
    ;; [ebp + 8] - start
    push dword [ebp + 8]
    call binary_search
    ;; 8 = 2 valori de 4 octeti pe stiva
    add esp, 8
    jmp end
not_greater:
    ;; start = mid + 1, end = end
    add dword [ebp + 8], 1
    ;; [ebp + 12] - end
    push dword [ebp + 12]
    ;; [ebp + 8] - start
    push dword [ebp + 8]
    call binary_search
    ;; 8 = 2 valori de 4 octeti pe stiva
    add esp, 8
    jmp end
ret_neg:
    ;; return -1
    mov eax, -1
end:
    ;; 1 = 1 valoare de 4 octeti pe stiva
    add esp, 4
    leave
    ret
