#include <stdint.h>

#ifndef PIOS_TXT_CONSOLE
#define PIOS_TXT_CONSOLE

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

/*!
    \brief Position of the cursor on the screen.

 */
class TxtCursor{
    public:
    int x = 0, y = 0;
};

/*!
    \brief Color Attribute byte of Text Mode.

    Made by 4bit_background << 4 | 4bit_foreground.
 */
class TxtAttribute{
    public:
        uint8_t attribute = 0x0f;
        TxtAttribute();
        TxtAttribute(uint8_t attribute);
        TxtAttribute(uint8_t background, uint8_t foreground);
};

/*!
    \brief Color Attribute and ASCII Character of Text Mode

 */
class TxtChar{
    public:
        uint8_t asciiChar; /**< \brief ASCII Character to print */
        TxtAttribute attribute; /**< Color Attribute */
        TxtChar(uint8_t asciiChar, uint8_t colorCode);
        TxtChar(uint8_t asciiChar, TxtAttribute attribute);
        uint16_t getValue(); /**< \brief get full value. @return 2 bytes: attribute << 8 | asciiChar*/
};

/*!
    \brief Text Mode console, use for early output

    You can use the << operator to print to the screen, much like with cout. 
    Works with char, \0 terminated char[], int; also takes TxtAttribute and applies them.
    Ex:
        console<<"Hello, World"<<'!'<<"    "<<TxtAttribute(0, 13)<<"2018"
 */
class TxtConsole{
    protected:
        int width = 80, height = 25;
        TxtCursor cursor;
        TxtAttribute attribute;
        uint16_t *videoMemory;
    public:
        TxtConsole(); /**< \brief initialize with default width and height. width: 80, height: 25. */
        TxtConsole(int width, int height); /**< \brief initialize with custom width and height. */
        void putChar(char c); /**< \brief writes a character at cursor position, with current attribute. @param c char to print. */
        void moveCursor(int x, int y);  /**< \brief moves the cursor to x, y. */
        void setAttribute(TxtAttribute attribute); /**<  \brief sets the attribute to use from now on. @param attribute TxtAttribute to use */
        void print(char *s); /**< \brief prints a \0 terminated character array to the screen */
        void clear(TxtChar tChar); /** \brief fills the screen with tChar */
        TxtConsole operator<<(char a); 
        TxtConsole operator<<(char a[]);
        TxtConsole operator<<(int d);
        TxtConsole operator<<(TxtAttribute attr);
    protected:
        int getIndexFromCoordinates(int x, int y);
};

namespace txt{
    void init();
    void putChar(char c); /**< \brief writes a character at cursor position, with current attribute. @param c char to print. */
    void moveCursor(int x, int y);  /**< \brief moves the cursor to x, y. */
    void setAttribute(TxtAttribute attribute); /**<  \brief sets the attribute to use from now on. @param attribute TxtAttribute to use */
    void clear(TxtChar tChar); /** \brief fills the screen with tChar */
    void kprintf(char *str);/**< \brief prints a \0 terminated character array to the screen */
    TxtConsole *getConsole();
}

#endif