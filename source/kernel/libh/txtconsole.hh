#include <stdint.h>

#define TXT_COLOR_BLACK 0
#define TXT_COLOR_BLUE 1
#define TXT_COLOR_GREEN 2
#define TXT_COLOR_CYAN 3
#define TXT_COLOR_RED 4
#define TXT_COLOR_MAGENTA 5
#define TXT_COLOR_BROWN 6
#define TXT_COLOR_LIGHT_GRAY 7
#define TXT_COLOR_DARK_GRAY 8
#define TXT_COLOR_LIGHT_BLUE 9
#define TXT_COLOR_LIGHT_GREEN 10
#define TXT_COLOR_LIGHT_CYAN 11
#define TXT_COLOR_LIGHT_RED 12
#define TXT_COLOR_LIGHT_MAGENTA 13
#define TXT_COLOR_YELLOW 14
#define TXT_COLOR_WHITE 15

class TxtCursor{
    public:
    int x = 0, y = 0;
};

class TxtAttribute{
    public:
        uint8_t attribute = 0x0f;
        TxtAttribute();
        TxtAttribute(uint8_t attribute);
        TxtAttribute(uint8_t background, uint8_t foreground);
};

class TxtChar{
    public:
        uint8_t asciiChar;
        TxtAttribute attribute;
        TxtChar(uint8_t asciiChar, uint8_t colorCode);
        TxtChar(uint8_t asciiChar, TxtAttribute attribute);
        uint16_t getValue();
};

class TxtConsole{
    protected:
        int width = 80, height = 25;
        TxtCursor cursor;
        TxtAttribute attribute;
        uint16_t *videoMemory;
    public:
        TxtConsole();
        TxtConsole(int width, int height);
        void putChar(char c);
        void moveCursor(int x, int y);
        void setAttribute(TxtAttribute attribute);
        void print(char *s);
        void clear(TxtChar tChar);
        TxtConsole operator<<(char a);
        TxtConsole operator<<(char a[]);
        TxtConsole operator<<(int d);
        TxtConsole operator<<(TxtAttribute attr);
    protected:
        int getIndexFromCoordinates(int x, int y);
};
