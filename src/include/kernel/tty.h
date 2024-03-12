#ifndef KERNEL_TTY_H
#define KERNEL_TTY_H

#include <stddef.h>

// void terminal_initalize(struct limine_framebuffer *framebuffer);
void terminal_putchar(char c);
void terminal_write(const char* data, size_t size);
void terminal_writestring(const char* data);

#endif