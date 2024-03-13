#include <kernel/tty.h>

#include <string.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <lib/ssfn.h>
#include <lib/multiboot.h>
#include <lib/incbin.h>

// INCBIN(ConsoleFont, "u_vga16.sfn");

// static int current_row = 0;

void terminal_initalize(struct multiboot_info *mbi) {
	/* set up context by global variables */
	// ssfn_src = & gConsoleFontData[0];      /* the bitmap font to use */

	ssfn_dst.ptr = mbi->framebuffer_addr;					/* address of the linear frame buffer */
	ssfn_dst.w = mbi->framebuffer_width;						/* width */
	ssfn_dst.h = mbi->framebuffer_height;						/* height */
	ssfn_dst.p = mbi->framebuffer_bpp * mbi->framebuffer_width / 8;	/* bytes per line */
	ssfn_dst.x = ssfn_dst.y = ssfn_src->width;							/* pen position */
	ssfn_dst.fg = 0xFFFFFF;		/* foreground color */ 						
}

void terminal_scroll(int line);

void terminal_putchar(char c) {
	ssfn_putc(c);
}

void terminal_write(const char* data, size_t size) {
	for (size_t i=0; i<size; i++) {
		terminal_putchar(data[i]);
	}
	terminal_putchar('\n');
}

terminal_writestring(const char* data) {
    // terminal_write(data, strlen(data));
}