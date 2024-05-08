#include <kernel/pit.h>

#include <kernel/io.h>
#include <kernel/pic.h>

#include <stdint.h>

void pit_initalize(uint32_t frequency) { // in hz
	cli();
	IRQ_clear_mask(0);
	uint32_t divisor = 1193180 / frequency;	/* Calculate our divisor */
    outb(0x43, 0x36);						/* Set our command byte 0x36 */
    outb(0x40, divisor & 0xFF);				/* Set low byte of divisor */
    outb(0x40, divisor >> 8);				/* Set high byte of divisor */
	sti();
}
 
uint32_t read_pit_count(void) {
	uint32_t count = 0;

	// Disable interrupts
	cli();

	// al = channel in bits 6 and 7, remaining bits clear
	outb(0x43,0b0000000);

	count = inb(0x40);		// Low byte
	count |= inb(0x40)<<8;		// High byte
	sti();

	return count;
}

void set_pit_count(uint16_t count) {
	// Disable interrupts
	cli();
 
	// Set low byte
	outb(0x40,count&0xFF);		// Low byte
	outb(0x40,(count&0xFF00)>>8);	// High byte
	
	sti();

	return;
}


uint32_t CountDown;
 
void sleep(uint32_t millis) {
    CountDown = millis;
    while (CountDown > 0)
        hlt();
}



void pit_irq_callback() {
	if (CountDown > 0) 
		CountDown--;
}
