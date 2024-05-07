#ifndef KERNEL_KEYBOARD_H
#define KERNEL_KEYBOARD_H

#include <stdint.h>

uint8_t scancode_to_ascii(uint8_t key);
void keyscan(void);

#endif
