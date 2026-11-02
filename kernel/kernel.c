char keymap[128] = {0, 0, '1','2','3','4','5','6','7','8','9','0','-','=', 0, 0, 'q','w','e','r','t','y','u','i','o','p','[',']', 0, 0, 'a','s','d','f','g','h','j','k','l',';','\'','`', 0, '\\', 'z','x','c','v','b','n','m',',','.','/', 0, '*', 0, ' '};
char keymap_shift[128] = {0, 0, '!','@','#','$','%','^','&','*','(',')','_','+', 0, 0, 'Q','W','E','R','T','Y','U','I','O','P','{','}', 0, 0, 'A','S','D','F','G','H','J','K','L',':','"','~', 0, '|', 'Z','X','C','V','B','N','M','<','>','?', 0, '*', 0, ' '};
int shift = 0;
int cursor = 80;
void print(char *str, int row, char color) {
    char *video = (char*) 0xB8000;
    int i = 0;
    while(str[i] != '\0') {
        video[(row * 80 + i) * 2] = str[i];
        video[(row * 80 + i) * 2 + 1] = color;
        i++;
    }
}

void clear() {
    char *video = (char*) 0xB8000;
    int i = 0;
    while (i < 2000) {    
        video[i * 2] = ' '; 
        video[i * 2 + 1] = 0x0F;
        i++;
    }
    
}

unsigned char inb(unsigned short port) {
    unsigned char result;
    asm volatile("inb %1, %0" : "=a" (result) : "Nd"(port));
    return result;
}

unsigned char outb(unsigned short port) {
    unsigned char result;
    asm volatile("outb %1, %0" : "=a" (result) : "Nd" (port));
}

void update_cursor(char cursor) {
    
}

void main() {
    clear();
    print("                                      MyOS        ", 0, 0x0D);
    char *video = (char*) 0xB8000;
    while (1) {
        if ((inb(0x64) & 1) == 0) {
            continue;
        } 
        unsigned char result = inb(0x60);
        if (result == 0x2A || result == 0x36) {
            shift = 1;
        } else if (result == 0xAA || result == 0xB6) {
            shift = 0;
        } else if (result == 0x0E) {
            if (cursor > 80) {
                cursor--;
                video[cursor * 2] = ' ';
            }
        } else if (result < 128) {
            if (shift == 1) {
                video[cursor * 2] = keymap_shift[result];
                video[cursor * 2 + 1] = 0x0F;
                cursor++;
            } else {
                video[cursor * 2] = keymap[result];
                video[cursor * 2 + 1] = 0x0F;
                cursor++;
            }
        } 
    } 
}