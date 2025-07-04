global moverBarco

section .text

; void moverBarco(int* x, int velocidad, int direccion)
; rdi = puntero a x (int)
; esi = velocidad (int)
; edx = direccion (int) → debe ser +1 (derecha) o -1 (izquierda)

moverBarco:
    mov eax, [rdi]    ; cargar x
    imul edx, esi     ; direccion * velocidad
    add eax, edx      ; x += direccion * velocidad
    mov [rdi], eax    ; guardar nuevo x
    ret
