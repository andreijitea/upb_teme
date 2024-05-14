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
    mov dword [esp - 4], 0
    mov eax, [ebp + 12]
    cmp eax, dword [ebp + 8]
    jl ret_neg
    ;; Calculeaza mijlocul listei
    add eax, dword [ebp + 8]
    sar eax, 1
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
    sub dword [ebp + 12], 1
    push dword [ebp + 12]
    push dword [ebp + 8]
    call binary_search
    add esp, 8
    jmp end
not_greater:
    ;; start = mid + 1, end = end
    add dword [ebp + 8], 1
    push dword [ebp + 12]
    push dword [ebp + 8]
    call binary_search
    add esp, 8
    jmp end
ret_neg:
    mov eax, -1
end:
    add esp, 4
    leave
    ret
