[org 0x7e00]
mov ax, 0
mov es,ax
mov bx, 0x8000
mov al, 4
mov cl, 3
call read_disk
jmp switch_pm
%include "print_string.asm" 
%include "read_disk.asm"
%include "gdt.asm"
%include "switch_pm.asm"
message: db "ad", 0
times 512-($-$$) db 0