global moverProyectil

section .text

; void moverProyectil(float* y, float velocidad)
; rdi = puntero a y (float)
; xmm0 = velocidad (float)

moverProyectil:
    movss xmm1, [rdi]   ; Cargar y en xmm1
    subss xmm1, xmm0    ; y -= velocidad (en punto flotante)
    movss [rdi], xmm1   ; Guardar el nuevo valor de y
    ret
