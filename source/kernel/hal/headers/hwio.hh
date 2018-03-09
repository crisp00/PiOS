#include <stdint.h>

static inline void io_wait(void)
{
    /* Port 0x80 is used for 'checkpoints' during POST. */
    /* The Linux kernel seems to think it is free for use :-/ */
    asm volatile("outb %%al, $0x80"
                 :
                 : "a"(0));
    /* %%al instead of %0 makes no difference.  TODO: does the register need to be zeroed? */
}
/*! @brief Write to hardware port.

 */
void outb(uint16_t port, uint8_t val);

/*! @brief Read from hardware port.

    Reading from a port consumes the value.
    @param port The port to read from.
    @return The read byte.
 */
uint8_t inb(uint16_t port);

