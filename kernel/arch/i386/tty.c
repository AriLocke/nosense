#include <kernel/tty.h>

#include <string.h>
#include <stdint.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <stdint.h> // Probably Necessary for SSFN
#include <lib/ssfn.h>
#include <lib/multiboot.h>
#include <lib/incbin.h>

#include <stdint.h>
INCBIN(ConsoleFont, "../lib/u_vga16.sfn");

static size_t terminal_row;
static size_t terminal_column;

static size_t terminal_width;
static size_t terminal_height;

// static char key_buffer[256]; 

void terminal_initalize(struct multiboot_info *mbi) {
	/* set up context by global variables */
	  terminal_row = 0;
	  terminal_column = 0;

	  ssfn_src = (ssfn_font_t *) &gConsoleFontData[0]; /* the bitmap font to use */

	  ssfn_dst.ptr = (uint8_t *)(uint64_t *) mbi->framebuffer_addr;					    /* address of the linear frame buffer */
	  ssfn_dst.w = mbi->framebuffer_width;                						/* width */
	  ssfn_dst.h = mbi->framebuffer_height;						                /* height */
	  ssfn_dst.p = mbi->framebuffer_bpp * mbi->framebuffer_width / 8;	/* bytes per line */
	  ssfn_dst.x = ssfn_dst.y = 0;                                    /* pen position */

    ssfn_dst.fg = 0xFFFFFF;		/* foreground color */ 

    terminal_width = ssfn_dst.w / ssfn_src->width;
    terminal_height = (ssfn_dst.h / ssfn_src->height) - 1;
}

void terminal_scroll(size_t lines) {
    if (lines > terminal_row)
        lines = terminal_row;

    uint32_t jumpbytes = lines * ssfn_dst.p * ssfn_src->height; // bytes to jump up by
    uint8_t* destination = ssfn_dst.ptr;
    uint8_t* source = destination + jumpbytes;
    uint32_t bytestomove = (ssfn_dst.p * ssfn_dst.h) - jumpbytes;

    memmove(destination, source, bytestomove);

    memset(destination + ((ssfn_dst.p * ssfn_dst.h) - jumpbytes), 0, jumpbytes);

    terminal_row -= lines;
}

void terminal_removechar() {

}

void terminal_putchar(char c) {
    ssfn_dst.x = terminal_column*ssfn_src->width; 
    ssfn_dst.y = terminal_row*ssfn_src->height;
    if (c == *"\b") {
        terminal_scroll(1);
        // terminal_column -= 1;
        return;
    } 
	  
    ssfn_putc(c);
  
    terminal_column += 1;

    if ((terminal_column >= terminal_width) || (c == '\n')) {
        if (terminal_row >= terminal_height)
            terminal_scroll(1);
        terminal_row += 1;
        terminal_column = 0;
    }
}

void terminal_write(const char* data, size_t size) {
    for (size_t i=0; i<size; i++)
        terminal_putchar(data[i]);
}

void terminal_writestring(const char* data) {
    terminal_write(data, strlen(data));
}
