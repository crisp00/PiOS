#include "../include/stdio.h"
#include "../include/txtmode.h"

void printf(const char* str){
    txt_putstring(str);
}