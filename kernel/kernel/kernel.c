#include <kernel/tty.h>
#include <kernel/gdt.h>
#include <kernel/idt.h>
#include <kernel/isrs.h>
#include <kernel/pic.h>

#include <lib/multiboot.h>

#include <stdbool.h>
#include <stdint.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

void hcf(void) {
    asm ("cli");
    for (;;) {
        asm ("hlt");
    }
}



multiboot_info_t *mbi;

void kernel_boot(uint32_t magic, uint32_t addr) {

	if (magic != MULTIBOOT_BOOTLOADER_MAGIC)
		hcf();

	mbi = (multiboot_info_t *) (uintptr_t) addr;
    
    gdt_install(); // maybe move these calls to boot.S
    idt_install();
    isrs_install();
    pic_initalize();
}

void kernel_main(void) {
    terminal_initalize(mbi);
	
    for(;;)
        asm ("hlt");
    
    hcf();
}
