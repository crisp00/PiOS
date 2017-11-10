#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>

void printf(const char* str);
char *itoa(unsigned i,unsigned base,char* buf);
char *itoa_s(int i,unsigned base,char* buf);
char* strcat(char *dest, const char* src);