#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <lib/multiboot.h>
#include <stddef.h>

void terminal_initalize(struct multiboot_info* mbi);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#endif
