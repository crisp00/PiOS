#include "headers/hwio.hh"

void outb(uint16_t port, uint8_t val)
{
    asm("outb %0, %1"
            :
            : "a"(val), "Nd"(port));
}

uint8_t inb(uint16_t port)
{
    uint8_t ret;
    asm("inb %1, %0"
            : "=a"(ret)
            : "Nd"(port));
    return ret;
}