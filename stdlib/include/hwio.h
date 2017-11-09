#ifndef __HWIO_H_INCLUDED__
#define __HWIO_H_INCLUDED__

#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#if !defined(__cplusplus)
#include <stdbool.h> /* C doesn't have booleans by default. */
#endif

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);


#endif