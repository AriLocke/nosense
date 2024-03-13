#include <kernel/tty.h>

#include <lib/multiboot.h>

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


// extern unsigned char _binary_libs_VGA[];
void kernel_main(unsigned long magic, unsigned long addr) {

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		hcf();

	multiboot_info_t *mbi = (multiboot_info_t *) addr;
	terminal_initalize(mbi);

	terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
	// terminal_write("123456789012345678901234567890", 30);
}
