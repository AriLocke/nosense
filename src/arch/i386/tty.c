#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <ssfn.h>
// #include <limine.h>
#include <incbin.h>

INCBIN(ConsoleFont, "libs/u_vga16.sfn");

static int current_row = 0;

// void terminal_initalize(struct limine_framebuffer *framebuffer) {
// 	/* set up context by global variables */
// 	ssfn_src = & gConsoleFontData[0];      /* the bitmap font to use */

// 	ssfn_dst.ptr = framebuffer->address;					/* address of the linear frame buffer */
// 	ssfn_dst.w = framebuffer->width;						/* width */
// 	ssfn_dst.h = framebuffer->height;						/* height */
// 	ssfn_dst.p = framebuffer->bpp * framebuffer->width / 8;	/* bytes per line */
// 	ssfn_dst.x = ssfn_dst.y = ssfn_src->width;							/* pen position */
// 	ssfn_dst.fg = 0xFFFFFF;									/* foreground color */
// }

void terminal_scroll(int line);

void terminal_putchar(char c) {
	// ssfn_putc(c);
}

void terminal_write(const char* data, size_t size) {
	for (size_t i=0; i<size; i++) {
		terminal_putchar(data[i]);
	}
	terminal_putchar('\n');
}
