#include <stdint.h>

extern "C" char *itoa(uint64_t num, char* str, int base);

char *ulltoa(unsigned long long num, char *str, int base);

extern "C" void log(char *str);