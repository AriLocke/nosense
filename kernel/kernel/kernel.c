#include <kernel/tty.h>

#include <lib/multiboot.h>
#include <stdio.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void hcf(void) {
	asm ("cli");
	for (;;) {
		asm ("hlt");
	}
}

multiboot_info_t *mbi;

void kernel_boot(unsigned long magic, unsigned long addr) {

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		hcf();

	mbi = (multiboot_info_t *) addr;
}

// extern unsigned char _binary_libs_VGA[];
void kernel_main(void) {
	terminal_initalize(mbi);
	terminal_writestring("termwritestring:");
	printf("printf:");
	// terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
}
