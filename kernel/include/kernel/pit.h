
#include <stdint.h>

void pit_initalize(uint32_t frequency);
void pit_irq_callback();

void sleep(uint32_t millis);
