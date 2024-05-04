%include "../include/io.mac"

extern ant_permissions

extern printf
global check_permission

section .text

check_permission:
    ;; DO NOT MODIFY
    push    ebp
    mov     ebp, esp
    pusha

    mov     eax, [ebp + 8]  ; id and permission
    mov     ebx, [ebp + 12] ; address to return the result
    ;; DO NOT MODIFY
   
    ;; Your code starts here

    ;; Calculeaza id furnica in ECX
    ;; Masca pentru id
    mov ecx, 0xFF000000
    ;; Aplica masca asupra primului argument
    and ecx, eax
    ;; Shift la dreapta pentru a obtine id-ul furnicii
    shr ecx, 24

    ;; Calculeaza lista de sali dorite de furnica in EDX
    ;; Masca pentru lista de sali
    mov edx, 0x00FFFFFF
    ;; Aplica masca asupra primului argument
    and edx, eax

    ;; Compara lista de sali dorite cu lista de sali permise
    ;; Salveaza in EAX lista de sali permise pentru furnica cu id-ul ECX
    shl ecx, 2
    mov eax, [ant_permissions + ecx]
    ;; Compara lista de sali dorite cu lista de sali permise
    and eax, edx
    cmp eax, edx
    ;; Daca cele 2 liste sunt diferite dupa operatia AND, furnica nu
    ;; are permisiunea de a intra in toate salile dorite -> returneaza 0, altfel 1
    setz byte [ebx]

    ;; Your code ends here
    
    ;; DO NOT MODIFY

    popa
    leave
    ret
    
    ;; DO NOT MODIFY
