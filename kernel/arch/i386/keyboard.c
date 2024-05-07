#include <kernel/keyboard.h>
#include <kernel/pic.h>

#include <stdio.h>

struct bitflags {
    uint8_t shift_held; // : 1?
	uint8_t caps_state;
};

static struct bitflags bf;


#define KEYBOARD_DATA_PORT   0x60
#define KEYBOARD_STATUS_PORT 0x64

enum SCANCODES {
	NULL_KEY = 0,
	Q_PRESSED = 0x10,
	W_PRESSED = 0x11,
	E_PRESSED = 0x12,
	R_PRESSED = 0x13,
	T_PRESSED = 0x14,
	Y_PRESSED = 0x15,
	U_PRESSED = 0x16,
	I_PRESSED = 0x17,
	O_PRESSED = 0x18,
	P_PRESSED = 0x19,
	A_PRESSED = 0x1E,
	S_PRESSED = 0x1F,
	D_PRESSED = 0x20,
	F_PRESSED = 0x21,
	G_PRESSED = 0x22,
	H_PRESSED = 0x23,
	J_PRESSED = 0x24,
	K_PRESSED = 0x25,
	L_PRESSED = 0x26,
	Z_PRESSED = 0x2C,
	X_PRESSED = 0x2D,
	C_PRESSED = 0x2E,
	V_PRESSED = 0x2F,
	B_PRESSED = 0x30,
	N_PRESSED = 0x31,
	M_PRESSED = 0x32,

	ONE_PRESSED = 0x2,
	NINE_PRESSED = 0xA,
	ZERO_PRESSED = 0xB,

	POINT_PRESSED = 0x34,
	POINT_RELEASED = 0xB4,

	SLASH_PRESSED = 0x35,
	
	BACKSPACE_PRESSED = 0xE,
	SPACE_PRESSED = 0x39,
	ENTER_PRESSED = 0x1C,

	LSHIFT_PRESSED = 0x2A,
	RSHIFT_PRESSED = 0x36,

	KEYBOARD_RELEASE = 0x80,
};

void to_upper(char* string)
{
    const char OFFSET = 'a' - 'A';
    // while (*string)
    // {
        *string = (*string >= 'a' && *string <= 'z') ? *string -= OFFSET : *string;
        string++;
    // }
}

static char* _qwertyuiop = "qwertyuiop";
static char* _asdfghjkl = "asdfghjkl";
static char* _zxcvbnm = "zxcvbnm";
static char* _num = "1234567890";

uint8_t scancode_to_ascii(uint8_t key)
{
	if(key == ENTER_PRESSED) return '\n';
	if(key == SPACE_PRESSED) return ' ';
	if(key == BACKSPACE_PRESSED) return '\b';
	if(key == POINT_PRESSED) return '.';
	if(key == SLASH_PRESSED) return '/';

	if(key >= ONE_PRESSED && key <= ZERO_PRESSED)
		return _num[key - ONE_PRESSED];
	
	if(key >= Q_PRESSED && key <= P_PRESSED)
		return _qwertyuiop[key - Q_PRESSED];

	if(key >= A_PRESSED && key <= L_PRESSED)
		return _asdfghjkl[key - A_PRESSED];
	
	if(key >= Z_PRESSED && key <= M_PRESSED)
		return _zxcvbnm[key - Z_PRESSED];

	return 0;
}

void keyscan(void) {
    uint8_t status;
    uint8_t keycode;

    status = inb(KEYBOARD_STATUS_PORT);
    /*Lowest bit of status will be set if buffer is not empty */
    if (status & 0x01) {
        keycode = inb(KEYBOARD_DATA_PORT);
       
        switch (keycode) {
            case (RSHIFT_PRESSED + KEYBOARD_RELEASE):
            case (LSHIFT_PRESSED + KEYBOARD_RELEASE):
                bf.shift_held = 0;
                break;

            case (RSHIFT_PRESSED):
            case (LSHIFT_PRESSED):
                bf.shift_held = 1;
                break;

            default:
                if (keycode > KEYBOARD_RELEASE) { // Key Release

                } else { // Key Press
                    char mappedkey = scancode_to_ascii(keycode);

                    if (bf.shift_held) {
                        to_upper(&mappedkey);
                    }

                    printf(&mappedkey);
                }
        }
    }
}
