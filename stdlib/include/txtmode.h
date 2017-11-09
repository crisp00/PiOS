#ifndef __TXTMODE_H_INCLUDED__
#define __TXTMODE_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif

#include "../include/hwio.h"

enum txt_color {
	TXT_COLOR_BLACK = 0,
	TXT_COLOR_BLUE = 1,
	TXT_COLOR_GREEN = 2,
	TXT_COLOR_CYAN = 3,
	TXT_COLOR_RED = 4,
	TXT_COLOR_MAGENTA = 5,
	TXT_COLOR_BROWN = 6,
	TXT_COLOR_LIGHT_GREY = 7,
	TXT_COLOR_DARK_GREY = 8,
	TXT_COLOR_LIGHT_BLUE = 9,
	TXT_COLOR_LIGHT_GREEN = 10,
	TXT_COLOR_LIGHT_CYAN = 11,
	TXT_COLOR_LIGHT_RED = 12,
	TXT_COLOR_LIGHT_MAGENTA = 13,
	TXT_COLOR_LIGHT_BROWN = 14,
	TXT_COLOR_WHITE = 15,
};

void txt_clearscreen();
uint8_t txt_modifier(enum txt_color bg, enum txt_color fg);
void txt_putstring(const char* str);
void txt_setcolor(enum txt_color bg, enum txt_color fg);
uint16_t txt_character (uint8_t modifier, uint8_t character);   
void txt_gotoxy(uint8_t x, uint8_t y); 

#endif