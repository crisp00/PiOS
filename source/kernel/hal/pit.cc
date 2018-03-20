#include "headers/pit.hh"
#include "headers/hwio.hh"

uint64_t pit_ticks = 0;
uint16_t pit_divider = 1000;


namespace pit{
uint64_t getTicks(){
    return pit_ticks;
}

void tick(){
    pit_ticks++;
}

void init(){
    asm("cli");
    outb(0x40,  (pit_divider & 255));
    outb(0x40,  (pit_divider / 256) & 255);
    return;
}

uint64_t millis(){
   return ((float)1000 / (1193182 / pit_divider)) * pit_ticks;
}
}