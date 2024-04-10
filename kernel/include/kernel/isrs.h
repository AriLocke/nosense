#ifndef KERNEL_ISRS_H
#define KERNEL_ISRS_H

/* This defines what the stack looks like after an ISR was running */
#include <stdint.h>
// struct __attribute__((packed)) regs
// {
//     unsigned int gs, fs, es, ds;      /* pushed the segs last */
//     unsigned int edi, esi, ebp, esp, ebx, edx, ecx, eax;  /* pushed by 'pusha' */
//     unsigned int int_no, err_code;    /* our 'push byte #' and ecodes do this */
//     unsigned int eip, cs, eflags, useresp, ss;   /* pushed by the processor automatically */ 
// };


void isrs_install();

// __attribute__((noreturn))
void fault_handler(uint32_t num);

void irq_handler(uint32_t num);

#endif
