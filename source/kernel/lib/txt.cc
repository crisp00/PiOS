#include "../libh/txt.hh"
#include "../hal/headers/hwio.hh"

#define TXT_WIDTH 80
#define TXT_HEIGHT 25

namespace txt{

int cur_x, cur_y;
uint8_t cur_modifier = 0x0f;
uint16_t* vidmem = (uint16_t*) 0xB8000;
uint16_t vidstack[TXT_WIDTH * TXT_HEIGHT];
int stack_cur_x, stack_cur_y;
uint8_t stack_modifier;

void init(){
    enable_cursor(0, 15);
}

int strlen(const char* str) {
	int len = 0;
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

void  clearscreen(){
    enable_cursor(0, 25);
    update_cursor(cur_x, cur_y);
    for(int y = 0; y < TXT_HEIGHT; y++){
        for(int x = 0; x < TXT_WIDTH; x++){
            vidmem[y * TXT_WIDTH + x] = character(cur_modifier, ' ');
        }
    }
}

void scrolldown(int lines){
    for(int y = lines - 1; y < TXT_HEIGHT - (lines - 1); y++){
        for(int x = 0; x < TXT_WIDTH; x++){
            vidmem[(y-lines) * TXT_WIDTH + x] = vidmem[y * TXT_WIDTH + x];
        }
    }
    for(int y = TXT_HEIGHT - lines; y < TXT_HEIGHT; y++){
        for(int x = 0; x < TXT_WIDTH; x++){
            vidmem[y * TXT_WIDTH + x] = character(cur_modifier, ' ');
        }
    }
}

void setcolor(uint8_t bg, uint8_t fg){
    cur_modifier = modifier(bg, fg);
}

uint8_t modifier(uint8_t bg, uint8_t fg){
    return bg * 0x10 + fg;
}

uint16_t character (uint8_t modifier, uint8_t character){
    return modifier * 0x100 + character;
}

void gotoxy(uint8_t x, uint8_t y){
    cur_x = x;
    cur_y = y;
    update_cursor(x, y);
}

void putchar(char character_){
    vidmem[cur_y * TXT_WIDTH + cur_x] = character(cur_modifier, character_);
}

void putstring(const char* str){
    int size = strlen(str);
    for(int i = 0; i < size; i++){
        bool newline = false;        
        if(str[i] == '\n'){
            newline = true;
        }else{
            putchar(str[i]);            
        }
        if(++cur_x == TXT_WIDTH || newline){
            cur_x = 0;
            if(++cur_y == TXT_HEIGHT){
                scrolldown(1);
                cur_y--;
            }
        }

    }
    update_cursor(cur_x, cur_y);
}

void push_screen(){
    stack_cur_x = cur_x;
    stack_cur_y = cur_y;
    stack_modifier = cur_modifier;
    for(int y = 0; y < TXT_HEIGHT; y++){
        for(int x = 0; x < TXT_WIDTH; x++){
            vidstack[y * TXT_WIDTH + x] = vidmem[y * TXT_WIDTH + x];
        }
    }
}

void pop_screen(){
    for(int y = 0; y < TXT_HEIGHT; y++){
        for(int x = 0; x < TXT_WIDTH; x++){
            vidmem[y * TXT_WIDTH + x] = vidstack[y * TXT_WIDTH + x];
        }
    }
    gotoxy(stack_cur_x, stack_cur_y);
    cur_modifier = stack_modifier;
}
}