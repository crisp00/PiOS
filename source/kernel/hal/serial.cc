#include "headers/serial.hh"

namespace serial{
    void init(){
        outb(SERIAL_PORT + 1, 0x00);    // Disable all interrupts
        outb(SERIAL_PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
        outb(SERIAL_PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
        outb(SERIAL_PORT + 1, 0x00);    //                  (hi byte)
        outb(SERIAL_PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
        outb(SERIAL_PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
        outb(SERIAL_PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
    }

    int check(){
        return inb(SERIAL_PORT + 5) & 1;
    }

    char read(){
        while (check() == 0);
 
        return inb(SERIAL_PORT);
    }

    int ready(){
        return inb(SERIAL_PORT + 5) & 0x20;
    }

    void write(char c){
        while (ready() == 0);

        outb(SERIAL_PORT, c);
    }

    void putstring(char *str){
        int i = 0;
        while(str[i] != '\0'){
            write(str[i]);
            i++;
        }
    }
}