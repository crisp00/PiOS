#include <stdint.h>
#include "hwio.hh"

#define SERIAL_PORT 0x3f8   /* COM1 */

namespace serial{
void init();

int check();

char read();

int ready();

void write(char a);

void putstring(char *str);

}
