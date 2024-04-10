#ifndef KERNEL_PIC_H
#define KERNEL_PIC_H

#include <stdint.h>

void outb(uint16_t port, uint8_t val);
uint8_t inb(uint16_t port);
void io_wait(void);

void pic_sendEOI(uint8_t irq);
void pic_remap(int offset1, int offset2);
void pic_disable(void);

void IRQ_set_mask(uint8_t IRQline);
void IRQ_clear_mask(uint8_t IRQline);

uint16_t pic_get_irr(void);
uint16_t pic_get_isr(void);

void pic_initalize(void);

#endif
