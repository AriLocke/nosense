#ifndef KERNEL_IDT_H
#define KERNEL_IDT_H

#include <stdint.h>
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint16_t flags);

void idt_install();

#endif
