#include "kernel.h"
#include <include/kernel/tty.h>

#include <stdint.h>
#include <stddef.h>
#include <stdbool.h>

#include <limine.h>

// Set the base revision to 1, this is recommended as this is the latest
// base revision described by the Limine boot protocol specification.
// See specification for further info.
 
#pragma region SysCalls
void *memcpy(void *dest, const void *src, size_t count) {
	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;
 
	for (size_t i = 0; i < count; i++) {
		pdest[i] = psrc[i];
	}
 
	return dest;
}
 
void *memset(void *dest, int ch, size_t count) {
	uint8_t *p = (uint8_t *)dest;
 
	for (size_t i = 0; i < count; i++) {
		p[i] = (uint8_t)ch;
	}
 
	return dest;
}
 
void *memmove(void *dest, const void *src, size_t count) {
	uint8_t *pdest = (uint8_t *)dest;
	const uint8_t *psrc = (const uint8_t *)src;
 
	if (src > dest) {
		for (size_t i = 0; i < count; i++) {
			pdest[i] = psrc[i];
		}
	} else if (src < dest) {
		for (size_t i = count; i > 0; i--) {
			pdest[i-1] = psrc[i-1];
		}
	}
 
	return dest;
}
 
int memcmp(const void *lhs, const void *rhs, size_t count) {
	const uint8_t *p1 = (const uint8_t *)lhs;
	const uint8_t *p2 = (const uint8_t *)rhs;
 
	for (size_t i = 0; i < count; i++) {
		if (p1[i] != p2[i]) {
			return p1[i] < p2[i] ? -1 : 1;
		}
	}
 
	return 0;
}
 
void hcf(void) {
	asm ("cli");
	for (;;) {
		asm ("hlt");
	}
}
#pragma endregion



static volatile LIMINE_BASE_REVISION(1);
 
static volatile struct limine_framebuffer_request framebuffer_request = {
	.id = LIMINE_FRAMEBUFFER_REQUEST,
	.revision = 0
};

// extern unsigned char _binary_libs_VGA[];
void _start(void) {
	// Ensure the bootloader actually understands our base revision (see spec).
	if (LIMINE_BASE_REVISION_SUPPORTED == false) {
		hcf();
	}
 
	// Ensure we got a framebuffer.
	if (framebuffer_request.response == NULL
	 || framebuffer_request.response->framebuffer_count < 1) {
		hcf();
	}

	// // Fetch the first framebuffer.
	struct limine_framebuffer *framebuffer = framebuffer_request.response->framebuffers[0];
	
	terminal_initalize(framebuffer);

	// // Note: we assume the framebuffer model is RGB with 32-bit pixels.
	for (size_t i = 0; i < 100; i++) {
		uint32_t *fb_ptr = framebuffer->address;
		fb_ptr[i * (framebuffer->pitch / 4) + i] = 0xaaffdd;
	}

	// We're done, just hang...
	hcf();
}
