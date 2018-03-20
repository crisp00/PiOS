#include <stdint.h>

namespace pit{
uint64_t getTicks();

void tick();

void init();

uint64_t millis();
}