#include "../include/stdio.h"
#include "../include/txtmode.h"

void printf(const char* str){
    txt_putstring(str);
}
char tbuf[32];
char bchars[] = {'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};

char *itoa(unsigned i,unsigned base,char* buf) {
   int pos = 0;
   int opos = 0;
   int top = 0;

   if (i == 0 || base > 16) {
      buf[0] = '0';
      buf[1] = 0;
      return buf;
   }

   while (i != 0) {
      tbuf[pos] = bchars[i % base];
      pos++;
      i /= base;
   }
   top=pos--;
   for (opos=0; opos<top; pos--,opos++) {
      buf[opos] = tbuf[pos];
   }
   buf[opos] = 0;
   return buf;
}

char *itoa_s(int i,unsigned base,char* buf) {
   if (base > 16) return 0;
   if (i < 0) {
      *buf++ = '-';
      i *= -1;
   }
   return itoa(i,base,buf);
}


char* strcat(char *dest, const char* src)
{
    size_t i,j;
    for (i = 0; dest[i] != '\0'; i++)
        ;
    for (j = 0; src[j] != '\0'; j++)
        dest[i+j] = src[j];
    dest[i+j] = '\0';
    return dest;
}