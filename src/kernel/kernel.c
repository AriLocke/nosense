#include "kernel.h"
#include <include/kernel/tty.h>

#include <multiboot.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#define CHECK_FLAG(flags,bit)   ((flags) & (1 << (bit)))

// Set the base revision to 1, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
 
#pragma region SysCalls
// void *memcpy(void *dest, const void *src, size_t count) {
// 	uint8_t *pdest = (uint8_t *)dest;
// 	const uint8_t *psrc = (const uint8_t *)src;
 
// 	for (size_t i = 0; i < count; i++) {
// 		pdest[i] = psrc[i];
// 	}
 
// 	return dest;
// }
 
// void *memset(void *dest, int ch, size_t count) {
// 	uint8_t *p = (uint8_t *)dest;
 
// 	for (size_t i = 0; i < count; i++) {
// 		p[i] = (uint8_t)ch;
// 	}
 
// 	return dest;
// }
 
// void *memmove(void *dest, const void *src, size_t count) {
// 	uint8_t *pdest = (uint8_t *)dest;
// 	const uint8_t *psrc = (const uint8_t *)src;
 
// 	if (src > dest) {
// 		for (size_t i = 0; i < count; i++) {
// 			pdest[i] = psrc[i];
// 		}
// 	} else if (src < dest) {
// 		for (size_t i = count; i > 0; i--) {
// 			pdest[i-1] = psrc[i-1];
// 		}
// 	}
 
// 	return dest;
// }
 
// int memcmp(const void *lhs, const void *rhs, size_t count) {
// 	const uint8_t *p1 = (const uint8_t *)lhs;
// 	const uint8_t *p2 = (const uint8_t *)rhs;
 
// 	for (size_t i = 0; i < count; i++) {
// 		if (p1[i] != p2[i]) {
// 			return p1[i] < p2[i] ? -1 : 1;
// 		}
// 	}
 
// 	return 0;
// }
 
void hcf(void) {
	asm ("cli");
	for (;;) {
		asm ("hlt");
	}
}
#pragma endregion


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
