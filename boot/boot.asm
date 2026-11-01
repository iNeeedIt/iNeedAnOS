[org 0x7c00]
mov ax, 0
mov es, ax
mov ah, 0x02
mov al, 1
mov cl, 2
mov ch, 0
mov dh, 0
mov dl, 0x80
mov bx, 0x7e00
int 0x13
jmp 0x7e00

times 510-($-$$) db 0

dw 0xAA55