
DEFAULT_HOST!=../utils/default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../utils/target-triplet-to-arch.sh $(HOST)
ARCHDIR=arch/$(HOSTARCH)

# $(info $$DEFAULT_HOST IS $(DEFAULT_HOST))
# $(info $$HOST IS $(HOST))
# $(info $$HOSTARCH IS $(HOSTARCH))
# $(info $$ARCHDIR IS $(ARCHDIR))

override KERNEL := nosense

CFLAGS?=-O2 # -g -pipe
CPPFLAGS?= # -std=gnu99
LDFLAGS?=-ffreestanding -O2 -nostdlib -lgcc
LIBS?=

CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -Iinclude #src -I libs# -D__is_kernel
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc

include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)


override CFILES := $(shell find -L * -type f -name '*.c')
override ASFILES := $(shell find -L * -type f -name '*.S')
override NASMFILES := $(shell find -L * -type f -name '*.asm')
override OBJ := $(addprefix obj/,$(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o))
override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))
 
# Default target.
.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S


all: nosense.kernel

# Link rules for the final kernel executable.
nosense.kernel: GNUmakefile linker.ld $(OBJ)
	mkdir -p "$$(dirname $@)"
	$(LD) linker.ld -o $@ $(LDFLAGS) $(OBJ)
 
# Include header dependencies.
-include $(HEADER_DEPS)
 
# Compilation rules for *.c files.
obj/%.c.o: ./%.c GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
 
# Compilation rules for *.S files.
obj/%.S.o: ./%.S GNUmakefile
	mkdir -p "$$(dirname $@)"
	$(AS) $(CFLAGS) $(CPPFLAGS) -c $< -o $@
 
# Compilation rules for *.asm (nasm) files.
obj/%.asm.o: ./%.asm GNUmakefile
	mkdir -p "$$(dirname $@)"
	nasm $(NASMFLAGS) $< -o $@
 
# Remove object files and the final executable.
.PHONY: clean
clean:
	rm -rf obj

install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
 
install-kernel: nosense.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp nosense.kernel $(DESTDIR)$(BOOTDIR)
 
-include $(OBJS:.o=.d)