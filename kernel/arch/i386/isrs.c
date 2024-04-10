#include "kernel/keyboard.h"
#include <kernel/isrs.h>
#include <kernel/idt.h>
#include <kernel/pic.h>

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
    idt_set_gate(0, (unsigned)isr0, 0x08, 0x8E);
    idt_set_gate(1, (unsigned)isr1, 0x08, 0x8E);
    idt_set_gate(2, (unsigned)isr2, 0x08, 0x8E);
    idt_set_gate(3, (unsigned)isr3, 0x08, 0x8E);
    idt_set_gate(4, (unsigned)isr4, 0x08, 0x8E);
    idt_set_gate(5, (unsigned)isr5, 0x08, 0x8E);
    idt_set_gate(6, (unsigned)isr6, 0x08, 0x8E);
    idt_set_gate(7, (unsigned)isr7, 0x08, 0x8E);
    idt_set_gate(8, (unsigned)isr8, 0x08, 0x8E);
    idt_set_gate(9, (unsigned)isr9, 0x08, 0x8E);
    idt_set_gate(10, (unsigned)isr10, 0x08, 0x8E);
    idt_set_gate(11, (unsigned)isr11, 0x08, 0x8E);
    idt_set_gate(12, (unsigned)isr12, 0x08, 0x8E);
    idt_set_gate(13, (unsigned)isr13, 0x08, 0x8E);
    idt_set_gate(14, (unsigned)isr14, 0x08, 0x8E);
    idt_set_gate(15, (unsigned)isr15, 0x08, 0x8E);
    idt_set_gate(16, (unsigned)isr16, 0x08, 0x8E);
    idt_set_gate(17, (unsigned)isr17, 0x08, 0x8E);
    idt_set_gate(18, (unsigned)isr18, 0x08, 0x8E);
    idt_set_gate(19, (unsigned)isr19, 0x08, 0x8E);
    idt_set_gate(20, (unsigned)isr20, 0x08, 0x8E);
    idt_set_gate(21, (unsigned)isr21, 0x08, 0x8E);
    idt_set_gate(22, (unsigned)isr22, 0x08, 0x8E);
    idt_set_gate(23, (unsigned)isr23, 0x08, 0x8E);
    idt_set_gate(24, (unsigned)isr24, 0x08, 0x8E);
    idt_set_gate(25, (unsigned)isr25, 0x08, 0x8E);
    idt_set_gate(26, (unsigned)isr26, 0x08, 0x8E);
    idt_set_gate(27, (unsigned)isr27, 0x08, 0x8E);
    idt_set_gate(28, (unsigned)isr28, 0x08, 0x8E);
    idt_set_gate(29, (unsigned)isr29, 0x08, 0x8E);
    idt_set_gate(30, (unsigned)isr30, 0x08, 0x8E);
    idt_set_gate(31, (unsigned)isr31, 0x08, 0x8E);
    idt_set_gate(32, (unsigned)isr32, 0x08, 0x8E);
    idt_set_gate(33, (unsigned)isr33, 0x08, 0x8E);
    idt_set_gate(34, (unsigned)isr34, 0x08, 0x8E);
    idt_set_gate(35, (unsigned)isr35, 0x08, 0x8E);
    idt_set_gate(36, (unsigned)isr36, 0x08, 0x8E);
    idt_set_gate(37, (unsigned)isr37, 0x08, 0x8E);
    idt_set_gate(38, (unsigned)isr38, 0x08, 0x8E);
    idt_set_gate(39, (unsigned)isr39, 0x08, 0x8E);
    idt_set_gate(40, (unsigned)isr40, 0x08, 0x8E);
    idt_set_gate(41, (unsigned)isr41, 0x08, 0x8E);
    idt_set_gate(42, (unsigned)isr42, 0x08, 0x8E);
    idt_set_gate(43, (unsigned)isr43, 0x08, 0x8E);
    idt_set_gate(44, (unsigned)isr44, 0x08, 0x8E);
    idt_set_gate(45, (unsigned)isr45, 0x08, 0x8E);
    idt_set_gate(46, (unsigned)isr46, 0x08, 0x8E);
    idt_set_gate(47, (unsigned)isr47, 0x08, 0x8E);
}

unsigned char *exception_messages[] =
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


void fault_handler(uint32_t eax) {
  /* Is this a fault whose number is from 0 to 31? */
    if (eax < 32) {
        char a[10];
        printf("\nInterupt ");
        printf(itoa(eax, a, 10));
        printf(", ");
        printf(exception_messages[eax]);
        printf(" Exception Occured. System Halted!\n");
        for (;;);
    } else {
        printf("Impossible Exception Called: ");
        char a[10];
        printf(itoa(eax, a, 10));
    }
}

void irq_handler(uint32_t eax) {

    // pic_sendEOI(1);
    
    if (eax == 33) { // Keyboard Interupt
        keyscan();
    } else {
        printf("\nUnhandled IRQ #");
        char a[10];
        printf(itoa(eax, a, 10));
    }
    pic_sendEOI(1);
}
