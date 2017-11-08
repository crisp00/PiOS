#include "../include/txtmode.h"

static size_t TXT_WIDTH = 80;
static size_t TXT_HEIGHT = 25;
size_t cur_x, cur_y;
size_t cur_modifier = 0x0f;
uint16_t* vidmem;

static inline void outb(uint16_t port, uint8_t val)
{
    __asm__ ( "outb %0, %1" : : "a"(val), "Nd"(port) );
    /* There's an outb %al, $imm8  encoding, for compile-time constant port numbers that fit in 8b.  (N constraint).
     * Wider immediate constants would be truncated at assemble-time (e.g. "i" constraint).
     * The  outb  %al, %dx  encoding is the only option for all other cases.
     * %1 expands to %dx because  port  is a uint16_t.  %w1 could be used if we had the port number a wider C type */
}

static inline uint8_t inb(uint16_t port)
{
    uint8_t ret;
    __asm__ ( "inb %1, %0"
                   : "=a"(ret)
                   : "Nd"(port) );
    return ret;
}

size_t strlen(const char* str) {
	size_t len = 0;
	while (str[len] != 0)
		len++;
	return len;
}

void enable_cursor(uint8_t cursor_start, uint8_t cursor_end)
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, (inb(0x3D5) & 0xC0) | cursor_start);
 
	outb(0x3D4, 0x0B);
	outb(0x3D5, (inb(0x3E0) & 0xE0) | cursor_end);
}

void disable_cursor()
{
	outb(0x3D4, 0x0A);
	outb(0x3D5, 0x20);
}

void update_cursor(int x, int y)
{
	uint16_t pos = y * TXT_WIDTH + x;
 
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t) (pos & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t) ((pos >> 8) & 0xFF));
}

void  txt_clearscreen(){
    TXT_WIDTH = 80;
    TXT_HEIGHT = 25;
    txt_gotoxy(0, 0);
    enable_cursor(0, 25);
    update_cursor(cur_x, cur_y);
    vidmem = (uint16_t*) 0xB8000;
    for(size_t y = 0; y < TXT_HEIGHT; y++){
        for(size_t x = 0; x < TXT_WIDTH; x++){
            vidmem[y * TXT_WIDTH + x] = txt_character(cur_modifier, ' ');
        }
    }
}

void txt_setcolor(enum txt_color bg, enum txt_color fg){
    cur_modifier = txt_modifier(bg, fg);
}

uint8_t txt_modifier(enum txt_color bg, enum txt_color fg){
    return bg * 0x10 + fg;
}

uint16_t txt_character (uint8_t modifier, uint8_t character){
    return modifier * 0x100 + character;
}

void txt_gotoxy(uint8_t x, uint8_t y){
    cur_x = x;
    cur_y = y;
    update_cursor(x, y);
}

void txt_putchar(char character){
    vidmem[cur_y * TXT_WIDTH + cur_x] =  txt_character(cur_modifier, character);
}

void txt_putstring(const char* str){
    size_t size = strlen(str);
    for(size_t i = 0; i < size; i++){
        bool newline = false;        
        if(str[i] == '\n'){
            newline = true;
        }else{
            txt_putchar(str[i]);            
        }
        if(++cur_x == TXT_WIDTH || newline){
            txt_gotoxy(0, cur_y + 1);
        }

    }
    update_cursor(cur_x, cur_y);
}