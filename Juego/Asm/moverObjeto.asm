global moverObjeto

section .text

; void moverObjeto(int* y, int velocidad)
; rdi = puntero a y (int)
; esi = velocidad

moverObjeto:
    mov eax, [rdi]  ; cargar y (32 bits)
    add eax, esi    ; sumar velocidad (32 bits)
    mov [rdi], eax  ; guardar nuevo y (32 bits)
    ret
