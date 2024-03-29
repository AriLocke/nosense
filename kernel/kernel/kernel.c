#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/pic.h>

#include <lib/multiboot.h>

#include <stdio.h>
#include <stdbool.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void hcf(void) {
	// asm ("cli");
	for (;;) {
		asm ("hlt");
	}
}



multiboot_info_t *mbi;

void kernel_boot(unsigned long magic, unsigned long addr) {

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		hcf();

	mbi = (multiboot_info_t *) addr;

  gdt_install(); // maybe move these calls to boot.S
  idt_install();
  isrs_install();
  pic_initalize();
}

// extern unsigned char _binary_libs_VGA[];
void kernel_main(void) {
	terminal_initalize(mbi);
	printf("test ----\n");
  // printf('a');
  // asm ("int $0x0000");
  // volatile int test = 0;
  // volatile int apple = 12 / test;
	printf("end test\n");
  hcf();
}
