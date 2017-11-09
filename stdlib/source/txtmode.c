#include "../include/txtmode.h"

static size_t TXT_WIDTH = 80;
static size_t TXT_HEIGHT = 25;
size_t cur_x, cur_y;
size_t cur_modifier = 0x0f;
uint16_t* vidmem = (uint16_t*) 0xB8000;

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
    enable_cursor(0, 25);
    update_cursor(cur_x, cur_y);
    for(size_t y = 0; y < TXT_HEIGHT; y++){
        for(size_t x = 0; x < TXT_WIDTH; x++){
            vidmem[y * TXT_WIDTH + x] = txt_character(cur_modifier, ' ');
        }
    }
}

void txt_scrolldown(size_t lines){
    for(size_t y = lines - 1; y < TXT_HEIGHT - (lines - 1); y++){
        for(size_t x = 0; x < TXT_WIDTH; x++){
            vidmem[(y-lines) * TXT_WIDTH + x] = vidmem[y * TXT_WIDTH + x];
        }
    }
    for(size_t y = TXT_HEIGHT - lines; y < TXT_HEIGHT; y++){
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
            cur_x = 0;
            if(++cur_y == TXT_HEIGHT){
                txt_scrolldown(1);
                cur_y--;
            }
        }

    }
    update_cursor(cur_x, cur_y);
}