#include <kernel/tty.h>

#include <string.h>

#define SSFN_CONSOLEBITMAP_TRUECOLOR        /* use the special renderer for 32 bit truecolor packed pixels */
#include <lib/ssfn.h>
#include <lib/multiboot.h>
#include <lib/incbin.h>
#include <stdlib.h>
#include <stdio.h>

INCBIN(ConsoleFont, "../lib/u_vga16.sfn");

// static int current_row = 0;

#define INT_DECIMAL_STRING_SIZE(int_type) ((CHAR_BIT*sizeof(int_type)-1)*10/33+3)

char *int_to_string_alloc(int x) {
  int i = x;
  char buf[INT_DECIMAL_STRING_SIZE(int)];
  char *p = &buf[sizeof buf] - 1;
  *p = '\0';
  if (i >= 0) {
    i = -i;
  }
  do {
    p--;
    *p = (char) ('0' - i % 10);
    i /= 10;
  } while (i);
  if (x < 0) {
    p--;
    *p = '-';
  }
  size_t len = (size_t) (&buf[sizeof buf] - p);
  char *s = malloc(len);
  // char *s = "00000000000000";
  if (s) {
    memcpy(s, p, len);
  }
  return s;
}



static size_t terminal_row;
static size_t terminal_column;

static size_t terminal_width;
static size_t terminal_height;

void terminal_initalize(struct multiboot_info *mbi) {
	/* set up context by global variables */
	terminal_row = 0;
	terminal_column = 0;

	ssfn_src = & gConsoleFontData[0];      /* the bitmap font to use */

	ssfn_dst.ptr = mbi->framebuffer_addr;					/* address of the linear frame buffer */
	ssfn_dst.w = mbi->framebuffer_width;						/* width */
	ssfn_dst.h = mbi->framebuffer_height;						/* height */
	ssfn_dst.p = mbi->framebuffer_bpp * mbi->framebuffer_width / 8;	/* bytes per line */
	ssfn_dst.x = ssfn_dst.y = 0;//ssfn_src->width;							/* pen position */

	ssfn_dst.fg = 0xFFFFFF;		/* foreground color */ 	

  terminal_width = ssfn_dst.w / ssfn_src->width;
  terminal_height = ssfn_dst.w / ssfn_src->height;


	// printf("screen: ");
	// char *w = int_to_string_alloc(mbi->framebuffer_width);
	// printf(w);
	
  // printf("x");
	// char *h = int_to_string_alloc(mbi->framebuffer_height);
	// printf(h);

  // printf(".   2845: ");
	// char *t = int_to_string_alloc(2845);
	// printf(t);
}

void terminal_scroll(int line) {
  
}

void terminal_putchar(char c) {
  ssfn_dst.x = terminal_column*ssfn_src->width; 
  ssfn_dst.y = terminal_row*ssfn_src->height;

	ssfn_putc(c);
  
  terminal_column += 1;

  if ((terminal_column >= terminal_width) || (c == '\n')) {
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