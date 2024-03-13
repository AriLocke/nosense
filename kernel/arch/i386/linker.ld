/* Tell the linker that we want an x86_64 ELF64 output file */
/* OUTPUT_FORMAT(elf64-x86-64)*/
/* OUTPUT_ARCH(i386:x86-64) */
 
/* Define the program headers we want so the bootloader gives us the right */
/* MMU permissions */
/* PHDRS
{ */
    /* text    PT_LOAD    FLAGS((1 << 0) | (1 << 2)) ; /* Execute + Read */
    /* rodata  PT_LOAD    FLAGS((1 << 2)) ;            Read only */
    /* data    PT_LOAD    FLAGS((1 << 1) | (1 << 2)) ; Write + Read */
    /* dynamic PT_DYNAMIC FLAGS((1 << 1) | (1 << 2)) ; Dynamic PHDR for relocations */
/* / */
    
ENTRY(_start)

/* Tell where the various sections of the object files will be put in the final
   kernel image. */
SECTIONS
{
	/* Begin putting sections at 1 MiB, a conventional place for kernels to be
	   loaded at by the bootloader. */
	. = 2M;

	/* First put the multiboot header, as it is required to be put very early
	   early in the image or the bootloader won't recognize the file format.
	   Next we'll put the .text section. */
	.text BLOCK(4K) : ALIGN(4K)
	{
		*(.multiboot)
		*(.text)
	}

	/* Read-only data. */
	.rodata BLOCK(4K) : ALIGN(4K)
	{
		*(.rodata)
	}

	/* Read-write data (initialized) */
	.data BLOCK(4K) : ALIGN(4K)
	{
		*(.data)
	}

	/* Read-write data (uninitialized) and stack */
	.bss BLOCK(4K) : ALIGN(4K)
	{
		*(COMMON)
		*(.bss)
	}

	/* The compiler may produce other sections, put them in the proper place in
	   in this file, if you'd like to include them in the final kernel. */
}
