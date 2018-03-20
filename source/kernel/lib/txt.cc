#include "../libh/txt.hh"
#include "../hal/headers/hwio.hh"
#include "../libh/stdlib.hh"

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

TxtConsole::TxtConsole(int width, int height){
    this->attribute = TxtAttribute(0x0f);
    this->width = width;
    this->height = height;
    this->videoMemory = (uint16_t*) 0xB8000;
    this->cursor = TxtCursor();
}

TxtConsole::TxtConsole(){
    this->attribute = TxtAttribute(0x0f);
    this->width = 80;
    this->height = 25;
    this->videoMemory = (uint16_t*) 0xB8000;
    this->cursor = TxtCursor();
}

int TxtConsole::getIndexFromCoordinates(int x, int y){
    return y * this->width + x;
}

void TxtConsole::putChar(char c){
    this->videoMemory[this->getIndexFromCoordinates(cursor.x, cursor.y)] = TxtChar(c, this->attribute).getValue();
    if(this->cursor.x < this->width){
        this->cursor.x++;
    }else{
        this->cursor.x = 0;
        this->cursor.y++;
    }
}

void TxtConsole::moveCursor(int x, int y){
    this->cursor.x = x;
    this->cursor.y = y;
}

void TxtConsole::clear(TxtChar tChar){
    for(int y = 0; y < this->height; y++){
        for(int x = 0; x < this->width; x++){
            this->moveCursor(x, y);
            this->setAttribute(tChar.attribute);
            this->putChar(tChar.asciiChar);
        }
    }
}

void TxtConsole::setAttribute(TxtAttribute attribute){
    this->attribute = attribute;
}

TxtConsole TxtConsole::operator<<(char a){
    this->putChar(a);
    return *this;
}

TxtConsole TxtConsole::operator<<(char a[]){
    int i = 0;
    while(a[i] != '\0'){
        this->putChar(a[i]);
        i++;
    }
    return *this;
}

static char *tmp;
TxtConsole TxtConsole::operator<<(int d){
    *this<<itoa(d, tmp, 10);
    return *this;
}

TxtConsole TxtConsole::operator<<(TxtAttribute attr){
    this->attribute = attr;
    return *this;
}

TxtChar::TxtChar(uint8_t asciiChar, uint8_t colorCode){
    this->asciiChar = asciiChar;
    this->attribute = TxtAttribute((char)colorCode);
}

TxtChar::TxtChar(uint8_t asciiChar, TxtAttribute attribute){
    this->asciiChar = asciiChar;
    this->attribute = attribute;
}

uint16_t TxtChar::getValue(){
    return (this->attribute.attribute << 8) | (this->asciiChar);
}

TxtAttribute::TxtAttribute(uint8_t background, uint8_t foreground){
    this->attribute = (background << 4) | foreground;
}

TxtAttribute::TxtAttribute(uint8_t attribute){
    this->attribute = attribute;
}

TxtAttribute::TxtAttribute(){

}