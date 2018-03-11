#include "../libh/txtconsole.hh"
#include "../libh/stdlib.hh"

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
    if(c == '\n'){
        this->moveCursor(0, this->cursor.y + 1);
    }else{
        this->videoMemory[this->getIndexFromCoordinates(cursor.x, cursor.y)] = TxtChar(c, this->attribute).getValue();
        if (this->cursor.x < this->width)
        {
            this->cursor.x++;
        }
        else
        {
            this->cursor.x = 0;
            this->cursor.y++;
        }
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

namespace txt{
    uint16_t width = 80, height = 25;
    uint16_t *vidmem = (uint16_t *)0xB8000;
    TxtAttribute cur_attr(TXT_COLOR_BLACK, TXT_COLOR_LIGHT_BLUE);
    TxtCursor cursor = TxtCursor();
    void putChar(char c){
        if(c == '\n'){
            moveCursor(0, cursor.y + 1);
        }else{
            vidmem[cursor.x + cursor.y * width] = TxtChar(c, cur_attr).getValue();
            if (cursor.x < width)
            {
                cursor.x++;
            }
            else
            {
                cursor.x = 0;
                cursor.y++;
            }
        }
    }
    void moveCursor(int x, int y){
        cursor.x = x;
        cursor.y = y;
    }
    void setAttribute(TxtAttribute attribute){
        cur_attr = attribute;
    }
    void clear(TxtChar tChar){
        setAttribute(tChar.attribute);
        for(int y = 0; y < height; y++){
            for(int x = 0; x < width; x++){
                moveCursor(x, y);
                putChar(tChar.asciiChar);
            }
        }
    }
    void kprintf(char *str){
        int i = 0;
        while(str[i] != '\0'){
            putChar(str[i]);
            i++;
        }
    }
}