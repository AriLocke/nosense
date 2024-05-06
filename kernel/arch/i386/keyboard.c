#include <kernel/keyboard.h>
#include <kernel/pic.h>

#include <stdio.h>

#define KEYBOARD_DATA_PORT   0x60
#define KEYBOARD_STATUS_PORT 0x64

struct bitflags {
    uint8_t shift_held : 1 ;
};

static struct bitflags bf;

char *keyboard_map[128] =
{
    0,  0, "1", "2", "3", "4", "5", "6", "7", "8", "9", "0", "-", "=", "\b",	/* Backspace */
  "\t" /* Tab */,	"q", "w", "e", "r",	"t", "y", "u", "i", "o", "p", "[", "]", "\n",	/* Enter key */
    0,			/* 29   - Control */
  "a", "s", "d", "f", "g", "h", "j", "k", "l", ";",	/* 39 */
 "\"", "`",   0,		/* Left shift */
 "\\", "z", "x", "c", "v", "b", "n",			/* 49 */
  "m", ",", ".", "/",   0,				/* Right shift */
  "*",
    0,	/* Alt */
  " ",	/* Space bar */
    0,	/* Caps lock */
    0,	/* 59 - F1 key ... > */
    0,   0,   0,   0,   0,   0,   0,   0,
    0,	/* < ... F10 */
    0,	/* 69 - Num lock*/
    0,	/* Scroll Lock */
    0,	/* Home key */
    0,	/* Up Arrow */
    0,	/* Page Up */
  "-",
    0,	/* Left Arrow */
    0,
    0,	/* Right Arrow */
  "+",
    0,	/* 79 - End key*/
    0,	/* Down Arrow */
    0,	/* Page Down */
    0,	/* Insert Key */
    0,	/* Delete Key */
    0,   0,   0,
    0,	/* F11 Key */
    0,	/* F12 Key */
    0,	/* All other keys are undefined */
};

#define KEYBOARD_RELEASE  0x80
#define LSHIFT_SCANCODE   0x2A
#define RSHIFT_SCANCODE   0x36

void to_upper(char* string)
{
    const char OFFSET = 'a' - 'A';
    // while (*string)
    // {
        *string = (*string >= 'a' && *string <= 'z') ? *string -= OFFSET : *string;
        string++;
    // }
}

void keyscan(void) {
    unsigned char status;
    unsigned char keycode;

    status = inb(KEYBOARD_STATUS_PORT);
    /*Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
       
        switch (keycode) {
            case (RSHIFT_SCANCODE + KEYBOARD_RELEASE):
            case (LSHIFT_SCANCODE + KEYBOARD_RELEASE):
                bf.shift_held = 0;
                break;

            case (RSHIFT_SCANCODE):
            case (LSHIFT_SCANCODE):
                bf.shift_held = 1;
                break;

            default:
                if (keycode > KEYBOARD_RELEASE) { // Key Release

                } else { // Key Press
                    char mappedkey = *keyboard_map[(unsigned char) keycode];
                    if (bf.shift_held) {
                        to_upper(&mappedkey);
                    }
                    printf(&mappedkey);
                }
        }
    }
}
