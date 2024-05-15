; Interpret as 64 bits code
[bits 64]

; nu uitati sa scrieti in feedback ca voiati
; assembly pe 64 de biti

section .text
global map
global reduce
;; void map(int64_t *destination_array, int64_t *source_array, int64_t array_size, int64_t(*f)(int64_t))
;; int64_t map_func1(int64_t curr_elem);
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
map_for_i:
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
	jl map_for_i

end_map:
	leave
	ret


; int reduce(int *dst, int *src, int n, int acc_init, int(*f)(int, int));
; int f(int acc, int curr_elem);
reduce:
	; look at these fancy registers
	push rbp
	mov rbp, rsp
	;; n = rdx
	mov rdx, [rbp + 16]
	;; src = rsi
	mov rsi, [rbp + 48]
	;; f = r8

	;; i = r9
	mov r9, 0

reduce_for_i:
	;; acc = f(acc, src[i])
	;; r10 = src[i]
	mov r10, [rsi + 8 * r9]
	;; Functia *f ia ca parametrii rdi si rsi,
	;; il modifica pe rdx (salvez in stack)
	mov r14, rdi
	mov rdi, rcx
	mov r15, rsi
	mov rsi, r10
	push rdx
	call r8
	pop rdx
	mov rdi, r14
	mov rsi, r15
	mov rcx, rax


	;; Incrementeaza i
	inc r9
	cmp r9, rdx
	jl reduce_for_i

end_reduce:
	mov rax, rcx
	leave
	ret

