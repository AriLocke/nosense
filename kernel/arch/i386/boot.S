#* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
#define EXT_C(sym)                     _ ## sym
#else
#define EXT_C(sym)                     sym
#endif

.set ALIGN,    		1<<0	# align loaded modules on page boundaries
.set MEMINFO,  		1<<1	# provide memory map
.set VIDEOINFO,		1<<2	# something
.set ADDRESSINFO,	1<<16	# something

.set FLAGS,    ALIGN | MEMINFO | VIDEOINFO		# this is the Multiboot 'flag' field
.set MAGIC,    0x1BADB002						# 'magic number' lets bootloader find the header
.set CHECKSUM, -(MAGIC + FLAGS)					# checksum of above, to prove we are multiboot
.set HEADER_ADDR, 0								# Unused unless ADDRESSINFO is flagged
.set LOAD_ADDR, 0								# Unused unless ADDRESSINFO is flagged
.set LOAD_END_ADDR, 0							# Unused unless ADDRESSINFO is flagged
.set BSS_END_ADDR, 0							# Unused unless ADDRESSINFO is flagged
.set ENTRY_ADDR, 0								# Unused unless ADDRESSINFO is flagged
.set MODE_TYPE, 0		
.set WIDTH, 0									# Prefered number of horizontal pixels
.set HEIGHT, 0									# Prefered number of vertical pixels
.set DEPTH, 32									# Prefered number of bits per pixel

.section .multiboot
.align 4
.long MAGIC			# Required
.long FLAGS			# Required
.long CHECKSUM		# Required
.long HEADER_ADDR	# Unused unless ADDREsSINFO is flagged
.long LOAD_ADDR		# Unused unless ADDRESSINFO is flagged
.long LOAD_END_ADDR	# Unused unless ADDRESSINFO is flagged
.long BSS_END_ADDR	# Unused unless ADDRESSINFO is flagged
.long ENTRY_ADDR	# Unused unless ADDRESSINFO is flagged
.long MODE_TYPE		# Unused unless VIDEOINFO is flagged
.long WIDTH			# Unused unless VIDEOINFO is flagged
.long HEIGHT		# Unused unless VIDEOINFO is flagged
.long DEPTH			# Unused unless VIDEOINFO is flagged

/*
The multiboot standard does not define the value of the stack pointer register
(esp) and it is up to the kernel to provide a stack. This allocates room for a
small stack by creating a symbol at the bottom of it, then allocating 16384
bytes for it, and finally creating a symbol at the top. The stack grows
downwards on x86. The stack is in its own section so it can be marked nobits,
which means the kernel file is smaller because it does not contain an
uninitialized stack. The stack on x86 must be 16-byte aligned according to the
System V ABI standard and de-facto extensions. The compiler will assume the
stack is properly aligned and failure to align the stack will result in
undefined behavior.
*/
.section .bss
.align 16
stack_bottom:
.skip 16384 # 16 KiB
stack_top:

/*
The linker script specifies _start as the entry point to the kernel and the
bootloader will jump to this position once the kernel has been loaded. It
doesn't make sense to return from this function as the bootloader is gone.
*/
.section .text
.global _start
.type _start, @function
_start:
    # Move the stack pointer to the location we want the stack to start
    mov $stack_top, %esp

   	# Reset EFLAGS.
    pushl   $0
    popf

    #* Push the pointer to the Multiboot information structure.
    pushl   %ebx
    #* Push the magic value.
    pushl   %eax
	
    call kernel_boot
    sti
  # cli

    call _init
    
    call kernel_main
    
    call hcf

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
# .size _start, . - _start

/* This will set up our new segment registers. We need to do
 something special in order to set CS. We do what is called a
 far jump. A jump that includes a segment as well as an offset.
 This is declared in C as 'extern void gdt_flush();' */
 
.global gdt_flush     # Allows the C code to link to this
.extern gp            # Says that '_gp' is in another file
gdt_flush:
    lgdt gp        # Load the GDT with our '_gp' which is a special pointer
    mov $0x10, %ax       # 0x10 is the offset in the GDT to our data segment
    mov %ax, %ds
    mov %ax, %es
    mov %ax, %fs
    mov %ax, %gs
    mov %ax, %ss
    jmp $0x08,$flush2 # 0x08 is the offset to our code segment: Far jump!

flush2:
    ret               # Returns back to the C

# Loads the IDT defined in '_idtp' into the processor.
# This is declared in C as 'extern void idt_load();'
.global idt_load
.extern idtp
idt_load:
    lidt idtp
    ret


# Generate Interupt Stubs
.extern fault_handler

.macro isr_err_stub num
.global isr\num
isr\num:
    pusha
    # cld
    push $\num
    call fault_handler
    pop %eax
    popa
    iret 
.endm

.macro isr_no_err_stub num
.global isr\num
isr\num:
    pusha
    # cld
    push $\num
    call fault_handler
    pop %eax
    popa
    iret 
.endm


.extern irq_handler
.extern printf

.macro isr_irq_stub num
.global isr\num
isr\num:
    pusha
    push $\num
    call irq_handler
    pop %eax
    popa
    iret
.endm

isr_no_err_stub 0   # Division By Zero
isr_no_err_stub 1   # Debug
isr_no_err_stub 2   # Non Maskable Interupt
isr_no_err_stub 3   # Breakpoint Exception 
isr_no_err_stub 4   # Into Detected Overflow
isr_no_err_stub 5   # Out of Bounds
isr_no_err_stub 6   # Invalid Opcode
isr_no_err_stub 7   # No Coprocessor
isr_err_stub    8   # Double Fault
isr_no_err_stub 9   # Coprocessor Segment Overrun
isr_err_stub    10  # Bad TSS
isr_err_stub    11  # Segment Not Present
isr_err_stub    12  # Stack Fault
isr_err_stub    13  # General Protection Fault
isr_err_stub    14  # Page Fault
isr_no_err_stub 15  # Unknown Interupt
isr_no_err_stub 16  # Coprocessor Fault
isr_err_stub    17  # Alignment Check (486+)
isr_no_err_stub 18  # Machine Check (Pentium/586+)
isr_no_err_stub 19  # Reserved
isr_no_err_stub 20  # Reserved
isr_no_err_stub 21  # Reserved
isr_no_err_stub 22  # Reserved
isr_no_err_stub 23  # Reserved
isr_no_err_stub 24  # Reserved
isr_no_err_stub 25  # Reserved
isr_no_err_stub 26  # Reserved
isr_no_err_stub 27  # Reserved
isr_no_err_stub 28  # Reserved
isr_no_err_stub 29  # Reserved
isr_err_stub    30  # Reserved
isr_no_err_stub 31  # Reserved

isr_irq_stub 32
isr_irq_stub 33
isr_irq_stub 34
isr_irq_stub 35
isr_irq_stub 36
isr_irq_stub 37
isr_irq_stub 38
isr_irq_stub 39
isr_irq_stub 40
isr_irq_stub 41
isr_irq_stub 42
isr_irq_stub 43
isr_irq_stub 44
isr_irq_stub 45
isr_irq_stub 46
isr_irq_stub 47
