#include <stdint.h>
#include "libh/txtconsole.hh"
#include "libh/stdlib.hh"
#include "hal/headers/idt.hh"

static char* tmp;
extern "C" void main(){
    TxtConsole console = TxtConsole();
    console.clear(TxtChar(' ', TxtAttribute(TXT_COLOR_WHITE, TXT_COLOR_DARK_GRAY)));
    console.moveCursor(0, 0);
    TxtAttribute test(TXT_COLOR_WHITE, TXT_COLOR_RED);
    install_idt();
    console<<"PiOS "<<2<<test<<" Going GOOD!!!";
}

extern "C" void CINTHandle(int errnum, int intnum){
    TxtConsole console = TxtConsole();
    console.clear(TxtChar(' ', TxtAttribute(TXT_COLOR_WHITE, TXT_COLOR_DARK_GRAY)));
    console.moveCursor(0, 0);
    TxtAttribute test(TXT_COLOR_WHITE, TXT_COLOR_RED);
    console<<"PiOS "<<2<<test<<" INTERRUPT!!!";

}