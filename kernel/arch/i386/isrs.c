#include <kernel/isrs.h>
#include <kernel/keyboard.h>
#include <kernel/isrs.h>
#include <kernel/idt.h>
#include <kernel/pic.h>
#include <kernel/pit.h>

#include <stdio.h>
#include <stdlib.h>

/* These are function prototypes for all of the exception
*  handlers: The first 32 entries in the IDT are reserved
*  by Intel, and are designed to service exceptions! */

extern void isr0();
extern void isr1();
extern void isr2();
extern void isr3();
extern void isr4();
extern void isr5();
extern void isr6();
extern void isr7();
extern void isr8();
extern void isr9();
extern void isr10();
extern void isr11();
extern void isr12();
extern void isr13();
extern void isr14();
extern void isr15();
extern void isr16();
extern void isr17();
extern void isr18();
extern void isr19();
extern void isr20();
extern void isr21();
extern void isr22();
extern void isr23();
extern void isr24();
extern void isr25();
extern void isr26();
extern void isr27();
extern void isr28();
extern void isr29();
extern void isr30();
extern void isr31();
extern void isr32();
extern void isr33();
extern void isr34();
extern void isr35();
extern void isr36();
extern void isr37();
extern void isr38();
extern void isr39();
extern void isr40();
extern void isr41();
extern void isr42();
extern void isr43();
extern void isr44();
extern void isr45();
extern void isr46();
extern void isr47();

/*  We set the access
*  flags to 0x8E. This means that the entry is present, is
*  running in ring 0 (kernel level), and has the lower 5 bits
*  set to the required '14', which is represented by 'E' in
*  hex. */
void isrs_install()
{
    idt_set_gate(0,  (uintptr_t)isr0, 0x08, 0x8E);
    idt_set_gate(1,  (uintptr_t)isr1, 0x08, 0x8E);
    idt_set_gate(2,  (uintptr_t)isr2, 0x08, 0x8E);
    idt_set_gate(3,  (uintptr_t)isr3, 0x08, 0x8E);
    idt_set_gate(4,  (uintptr_t)isr4, 0x08, 0x8E);
    idt_set_gate(5,  (uintptr_t)isr5, 0x08, 0x8E);
    idt_set_gate(6,  (uintptr_t)isr6, 0x08, 0x8E);
    idt_set_gate(7,  (uintptr_t)isr7, 0x08, 0x8E);
    idt_set_gate(8,  (uintptr_t)isr8, 0x08, 0x8E);
    idt_set_gate(9,  (uintptr_t)isr9, 0x08, 0x8E);
    idt_set_gate(10, (uintptr_t)isr10, 0x08, 0x8E);
    idt_set_gate(11, (uintptr_t)isr11, 0x08, 0x8E);
    idt_set_gate(12, (uintptr_t)isr12, 0x08, 0x8E);
    idt_set_gate(13, (uintptr_t)isr13, 0x08, 0x8E);
    idt_set_gate(14, (uintptr_t)isr14, 0x08, 0x8E);
    idt_set_gate(15, (uintptr_t)isr15, 0x08, 0x8E);
    idt_set_gate(16, (uintptr_t)isr16, 0x08, 0x8E);
    idt_set_gate(17, (uintptr_t)isr17, 0x08, 0x8E);
    idt_set_gate(18, (uintptr_t)isr18, 0x08, 0x8E);
    idt_set_gate(19, (uintptr_t)isr19, 0x08, 0x8E);
    idt_set_gate(20, (uintptr_t)isr20, 0x08, 0x8E);
    idt_set_gate(21, (uintptr_t)isr21, 0x08, 0x8E);
    idt_set_gate(22, (uintptr_t)isr22, 0x08, 0x8E);
    idt_set_gate(23, (uintptr_t)isr23, 0x08, 0x8E);
    idt_set_gate(24, (uintptr_t)isr24, 0x08, 0x8E);
    idt_set_gate(25, (uintptr_t)isr25, 0x08, 0x8E);
    idt_set_gate(26, (uintptr_t)isr26, 0x08, 0x8E);
    idt_set_gate(27, (uintptr_t)isr27, 0x08, 0x8E);
    idt_set_gate(28, (uintptr_t)isr28, 0x08, 0x8E);
    idt_set_gate(29, (uintptr_t)isr29, 0x08, 0x8E);
    idt_set_gate(30, (uintptr_t)isr30, 0x08, 0x8E);
    idt_set_gate(31, (uintptr_t)isr31, 0x08, 0x8E);
    idt_set_gate(32, (uintptr_t)isr32, 0x08, 0x8E);
    idt_set_gate(33, (uintptr_t)isr33, 0x08, 0x8E);
    idt_set_gate(34, (uintptr_t)isr34, 0x08, 0x8E);
    idt_set_gate(35, (uintptr_t)isr35, 0x08, 0x8E);
    idt_set_gate(36, (uintptr_t)isr36, 0x08, 0x8E);
    idt_set_gate(37, (uintptr_t)isr37, 0x08, 0x8E);
    idt_set_gate(38, (uintptr_t)isr38, 0x08, 0x8E);
    idt_set_gate(39, (uintptr_t)isr39, 0x08, 0x8E);
    idt_set_gate(40, (uintptr_t)isr40, 0x08, 0x8E);
    idt_set_gate(41, (uintptr_t)isr41, 0x08, 0x8E);
    idt_set_gate(42, (uintptr_t)isr42, 0x08, 0x8E);
    idt_set_gate(43, (uintptr_t)isr43, 0x08, 0x8E);
    idt_set_gate(44, (uintptr_t)isr44, 0x08, 0x8E);
    idt_set_gate(45, (uintptr_t)isr45, 0x08, 0x8E);
    idt_set_gate(46, (uintptr_t)isr46, 0x08, 0x8E);
    idt_set_gate(47, (uintptr_t)isr47, 0x08, 0x8E);
}

char *exception_messages[] =
{
    "Division By Zero",               
    "Debug",
    "Non Maskable Interrupt",
    "Breakpoint Exception",
    "Into Detected Overflow",
    "Out of Bounds",
    "Invalid Opcode",
    "No Coprocessor",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Bad TSS",
    "Segment Not Present",
    "Stack Fault",
    "General Protection Fault",
    "Page Fault",
    "Unknown Interrupt",
    "Coprocessor Fault",
    "Alignment Check (486+)",
    "Machine Check (Pentium/586+)",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved"
};


void fault_handler(uint32_t num) {
  /* Is this a fault whose number is from 0 to 31? */
    if (num < 32) {
        char a[10];
        printf("\nInterupt ");
        printf(itoa(num, a, 10));
        printf(", ");
        printf(exception_messages[num]);
        printf(" Exception Occured. System Halted!\n");
        for (;;);
    } else {
        printf("Impossible Exception Called: ");
        char a[10];
        printf(itoa(num, a, 10));
    }
}

void irq_handler(uint32_t num) {

    // pic_sendEOI(1);
	
	switch (num) {
		case 32:
			pit_irq_callback();
			break;
		case 33:
	        keyscan();
			break;
		default:
			printf("\nUnhandled IRQ #");
			char a[4];
			printf(itoa(num, a, 10));
	}

    pic_sendEOI(1);
}
