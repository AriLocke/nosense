#include <kernel/idt.h>

#include <stdint.h>
#include <string.h>

struct idt_entry
{
  uint16_t base_lo;
  uint16_t sel;        /* Our kernel segment goes here! */
  uint8_t always0;     /* This will ALWAYS be set to 0! */
  uint8_t flags;       /* Set using the above table! */
  uint16_t base_hi;
} __attribute__((packed));

struct idt_ptr
{
    uint16_t limit;
    uint32_t base;
} __attribute__((packed));

/* Declare an IDT of 256 entries. Although we will only use the
*  first 32 entries in this tutorial, the rest exists as a bit
*  of a trap. If any undefined IDT entry is hit, it normally
*  will cause an "Unhandled Interrupt" exception. Any descriptor
*  for which the 'presence' bit is cleared (0) will generate an
*  "Unhandled Interrupt" exception */
struct idt_entry idt[256];
struct idt_ptr idtp;

/* This exists in 'start.asm', and is used to load our IDT */
extern void idt_load();

/* Use this function to set an entry in the IDT. Alot simpler
*  than twiddling with the GDT ;) */
void idt_set_gate(uint8_t num, uint64_t base, uint16_t sel, uint16_t flags) {
  /* Setup the descriptor base address */
  idt[num].base_lo = (base & 0xFFFF);
  idt[num].base_hi = (base >> 16) & 0xFFFF;
 
  /* Setup sel and flags */
  idt[num].sel = sel;
  idt[num].flags = flags;

  /* Ensure always0 is 0 */
  idt[num].always0 = 0;
}

/* Installs the IDT */
void idt_install() {
    /* Sets the special IDT pointer up, just like in 'gdt.c' */
    idtp.limit = (sizeof (struct idt_entry) * 256) - 1;
    idtp.base = (uintptr_t) &idt;

    /* Clear out the entire IDT, initializing it to zeros */
    memset(&idt, 0, sizeof(struct idt_entry) * 256);

    /* Add any new ISRs to the IDT here using idt_set_gate */

    /* Points the processor's internal register to the new IDT */
    idt_load();
}

