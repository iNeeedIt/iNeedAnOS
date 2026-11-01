print_string:
    .boucle:
        mov al, [bx]
        cmp al, 0
        je .fin
        int 0x10
        inc bx
        jmp .boucle
        .fin:
            ret