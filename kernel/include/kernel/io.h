#ifndef KERNEL_IO_H
#define KERNEL_IO_H

#include <stdint.h>

void hlt();
void cli();
void sti();

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);

#endif
