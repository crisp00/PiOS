#include <stdint.h>
#include "../../entry.hh"

void init_test();

extern "C" void PIOS_install_idt();

void install_idt(bool debug_);

void fill_idt(int index, IDTDescr descr);

IDTDescr_t makeDescriptor(uint32_t addr, uint16_t selector);
