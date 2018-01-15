#include "../include/keyboard.h"

const char KBD_SCANCODES[] = {
    [0x1] = 13,
    [0x39] = ' ',
    [0x1C] = '\n',

    [0x2] = '1',
    [0x3] = '2',
    [0x4] = '3',
    [0x5] = '4',
    [0x6] = '5',
    [0x7] = '6',
    [0x8] = '7',
    [0x9] = '8',
    [0xA] = '9',
    [0xB] = '0',

    [0x1E] = 'A',
    [0x30] = 'B',
    [0x2E] = 'C',
    [0x20] = 'D',
    [0x12] = 'E',
    [0x21] = 'F',
    [0x22] = 'G',
    [0x23] = 'H',
    [0x17] = 'I',
    [0x24] = 'J',
    [0x25] = 'K',
    [0x26] = 'L',
    [0x32] = 'M',
    [0x31] = 'N',
    [0x18] = 'O',
    [0x19] = 'P',
    [0x10] = 'Q',
    [0x13] = 'R',
    [0x1F] = 'S',
    [0x14] = 'T',
    [0x16] = 'U',
    [0x2F] = 'V',
    [0x11] = 'W',
    [0x2D] = 'X',
    [0x15] = 'Y',
    [0x2C] = 'Z',


};

uint8_t kbd_getscancode(){
    char c=0;
    while(inb(0x64) % 2 == 0){
        __asm__("nop");
    }
    do {
        if(inb(0x60)!=c) {
            c=inb(0x60);
            if(c>0)
                return c;
        }
    } while(1);
}

char kbd_getchar(){
    return KBD_SCANCODES[kbd_getscancode()];
}

char* kbd_getstring(char* tmp){
    char c;
    char* str = tmp;
    size_t i = 0;
    do{
        c = kbd_getchar();
        char c_[] = {c, '\0'};
        printf(c_);
        str[i] = c;
        i++;
    }while(c != '\n');
    str[i] = '\0';

    return str;
}
