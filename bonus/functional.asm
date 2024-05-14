; Interpret as 64 bits code
[bits 64]

; nu uitati sa scrieti in feedback ca voiati
; assembly pe 64 de biti

section .text
global map
global reduce
;; void map(int64_t *destination_array, int64_t *source_array, int64_t array_size, int64_t(*f)(int64_t))
map:
    xor rax, rax
    ; look at these fancy registers
    push rbp
    mov rbp, rsp
    ;; array_size = rdx
    mov rdx, [rbp + 16]
    ;; source_array = rsi
    mov rsi, [rbp + 48]
    ;; destination_array = rdi
    mov rdi, [rbp + 56]
    ;; f = rcx

    ;; i = r8
    mov r8, 0
for_i:
    ;; r9 = source_array[i]
    mov r9, [rsi + 8 * r8]

    ;; r9 = f(r9)
    ;; Functia *f ia ca parametru rdi
    mov rbx, rdi
    mov rdi, r9
    call rcx
    mov r9, rax
    mov rdi, rbx

    ;; destination_array[i] = r9
    mov qword [rdi + 8 * r8], r9
    
    ;; Incrementeaza for_i
    inc r8
    cmp r8, rdx
    jl for_i

end_map:
    leave
    ret


; int reduce(int *dst, int *src, int n, int acc_init, int(*f)(int, int));
; int f(int acc, int curr_elem);
reduce:
    ; look at these fancy registers
    push rbp
    mov rbp, rsp

    ; sa-nceapa festivalu'

    leave
    ret

