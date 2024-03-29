/* C symbol format. HAVE_ASM_USCORE is defined by configure. */
#ifdef HAVE_ASM_USCORE
#define EXT_C(sym)                     _ ## sym
#else
#define EXT_C(sym)                     sym
#endif
#define STACK_SIZE                      0x4000

.set ALIGN,    		1<<0			/* align loaded modules on page boundaries */
.set MEMINFO,  		1<<1			/* provide memory map */
.set VIDEOINFO,		1<<2			/* provide memory map */
.set ADDRESSINFO,	1<<16			/* provide memory map */

.set FLAGS,    ALIGN | MEMINFO | VIDEOINFO	/* this is the Multiboot 'flag' field */
.set MAGIC,    0x1BADB002       			/* 'magic number' lets bootloader find the header */
.set CHECKSUM, -(MAGIC + FLAGS) 			/* checksum of above, to prove we are multiboot */
.set HEADER_ADDR, 0		# Unused unless ADDRESSINFO is flagged
.set LOAD_ADDR, 0		# Unused unless ADDRESSINFO is flagged
.set LOAD_END_ADDR, 0	# Unused unless ADDRESSINFO is flagged
.set BSS_END_ADDR, 0	# Unused unless ADDRESSINFO is flagged
.set ENTRY_ADDR, 0		# Unused unless ADDRESSINFO is flagged
.set MODE_TYPE, 0		
.set WIDTH, 0			# Prefered number of horizontal pixels
.set HEIGHT, 0			# Prefered number of vertical pixels
.set DEPTH, 32			# Prefered number of bits per pixel

.section .multiboot
.align 4
.long MAGIC	# Required
.long FLAGS				# Required
.long CHECKSUM			# Required
.long HEADER_ADDR		# Unused unless ADDREsSINFO is flagged
.long LOAD_ADDR			# Unused unless ADDRESSINFO is flagged
.long LOAD_END_ADDR		# Unused unless ADDRESSINFO is flagged
.long BSS_END_ADDR		# Unused unless ADDRESSINFO is flagged
.long ENTRY_ADDR		# Unused unless ADDRESSINFO is flagged
.long MODE_TYPE			# Unused unless VIDEOINFO is flagged
.long WIDTH				# Unused unless VIDEOINFO is flagged
.long HEIGHT			# Unused unless VIDEOINFO is flagged
.long DEPTH				# Unused unless VIDEOINFO is flagged

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
	/*
	To set up a stack, we set the esp register to point to the top of the
	stack (as it grows downwards on x86 systems). This is necessarily done
	in assembly as languages such as C cannot function without a stack.
	*/
	mov $stack_top, %esp

	/* Initialize the stack pointer. */
	/*  movl    $(stack + STACK_SIZE), %esp */

	/* Reset EFLAGS. */
	pushl   $0
	popf

	/* Push the pointer to the Multiboot information structure. */
	pushl   %ebx
	/* Push the magic value. */
	pushl   %eax
	
	call kernel_boot

	call _init
	
	/*
	Enter the high-level kernel. The ABI requires the stack is 16-byte
	aligned at the time of the call instruction (which afterwards pushes
	the return pointer of size 4 bytes). The stack was originally 16-byte
	aligned above and we've pushed a multiple of 16 bytes to the
	stack since (pushed 0 bytes so far), so the alignment has thus been
	preserved and the call is well defined.
	*/
	call kernel_main

	/*
	If the system has nothing more to do, put the computer into an
	infinite loop. */
	call hcf

/*
Set the size of the _start symbol to the current location '.' minus its start.
This is useful when debugging or when you implement call tracing.
*/
.size _start, . - _start

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
