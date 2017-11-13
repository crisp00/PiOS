#ifndef __KEYBOARD_H_INCLUDED__
#define __KEYBOARD_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif

#include "../include/hwio.h"
#include "../include/stdio.h"




uint8_t kbd_getscancode();
char* kbd_getstring(char* tmp);    
    

#endif