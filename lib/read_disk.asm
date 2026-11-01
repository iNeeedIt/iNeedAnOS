read_disk:
    mov ah, 0x02
    mov ch, 0
    mov dh, 0
    mov dl, 0x80
    int 0x13
    jc .erreur
    ret
    .erreur:
        mov ah, 0x0e
        mov bx, .msg
        call print_string
        jmp $

.msg:
db "Erreur Disque", 0
        
