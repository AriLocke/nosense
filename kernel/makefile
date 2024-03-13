
DEFAULT_HOST!=../utils/default-host.sh
HOST?=$(DEFAULT_HOST)
HOSTARCH!=../utils/target-triplet-to-arch.sh $(HOST)
ARCHDIR=arch/$(HOSTARCH)

# $(info $$DEFAULT_HOST IS $(DEFAULT_HOST))
# $(info $$HOST IS $(HOST))
# $(info $$HOSTARCH IS $(HOSTARCH))
# $(info $$ARCHDIR IS $(ARCHDIR))

# CFLAGS?=-O2 # -g -pipe
# CPPFLAGS?= # -std=gnu99
# LDFLAGS?=-ffreestanding -O2 -nostdlib -lgcc
# LIBS?=

# DESTDIR?=
# PREFIX?=/usr/local
# EXEC_PREFIX?=$(PREFIX)
# BOOTDIR?=$(EXEC_PREFIX)/boot
# INCLUDEDIR?=$(PREFIX)/include

# CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
# CPPFLAGS:=$(CPPFLAGS) -Iinclude #src -I libs# -D__is_kernel
# LDFLAGS:=$(LDFLAGS)
# LIBS:=$(LIBS) -nostdlib -lk -lgcc

# include $(ARCHDIR)/make.config
 
# CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
# CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
# LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
# LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)


# override CFILES := $(shell find -L * -type f -name '*.c')
# override ASFILES := $(shell find -L * -type f -name '*.S')
# override NASMFILES := $(shell find -L * -type f -name '*.asm')
# override OBJ := $(CFILES:.c=.c.o) $(ASFILES:.S=.S.o) $(NASMFILES:.asm=.asm.o)
# override HEADER_DEPS := $(addprefix obj/,$(CFILES:.c=.c.d) $(ASFILES:.S=.S.d))

CFLAGS?=-O2 -g
CPPFLAGS?=
LDFLAGS?=
LIBS?=
 
DESTDIR?=
PREFIX?=/usr/local
EXEC_PREFIX?=$(PREFIX)
BOOTDIR?=$(EXEC_PREFIX)/boot
INCLUDEDIR?=$(PREFIX)/include
 
CFLAGS:=$(CFLAGS) -ffreestanding -Wall -Wextra
CPPFLAGS:=$(CPPFLAGS) -D__is_kernel -Iinclude
LDFLAGS:=$(LDFLAGS)
LIBS:=$(LIBS) -nostdlib -lk -lgcc
 
ARCHDIR=arch/$(HOSTARCH)
 
include $(ARCHDIR)/make.config
 
CFLAGS:=$(CFLAGS) $(KERNEL_ARCH_CFLAGS)
CPPFLAGS:=$(CPPFLAGS) $(KERNEL_ARCH_CPPFLAGS)
LDFLAGS:=$(LDFLAGS) $(KERNEL_ARCH_LDFLAGS)
LIBS:=$(LIBS) $(KERNEL_ARCH_LIBS)
 
KERNEL_OBJS=$(KERNEL_ARCH_OBJS) kernel/kernel.o
 
OBJS=\
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \
 
LINK_LIST=\
$(LDFLAGS) \
$(ARCHDIR)/crti.o \
$(ARCHDIR)/crtbegin.o \
$(KERNEL_OBJS) \
$(LIBS) \
$(ARCHDIR)/crtend.o \
$(ARCHDIR)/crtn.o \

# Default target.
.PHONY: all clean install install-headers install-kernel
.SUFFIXES: .o .c .S

all: nosense.kernel
$(info --------------------------------------------------------------------)
$(info SHELL FIND: $(shell find -L * -type f -name '*.o'))
$(info LINK_LIST: $(LINK_LIST))
$(info KERNEL_ARCH_OBJS: $(KERNEL_ARCH_OBJS))
$(info --------------------------------------------------------------------)

nosense.kernel: $(OBJS) $(ARCHDIR)/linker.ld
	$(CC) -T $(ARCHDIR)/linker.ld -o $@ $(CFLAGS) $(LINK_LIST)
	grub-file --is-x86-multiboot nosense.kernel
 
$(ARCHDIR)/crtbegin.o $(ARCHDIR)/crtend.o:
	OBJ=`$(CC) $(CFLAGS) $(LDFLAGS) -print-file-name=$(@F)` && cp "$$OBJ" $@
 
.c.o:
	$(CC) -MD -c $< -o $@ -std=gnu11 $(CFLAGS) $(CPPFLAGS)
 
.S.o:
	$(CC) -MD -c $< -o $@ $(CFLAGS) $(CPPFLAGS)

	
clean:
	rm -f nosense.kernel
	rm -f $(OBJS) *.o */*.o */*/*.o
	rm -f $(OBJS:.o=.d) *.d */*.d */*/*.d

install: install-headers install-kernel
 
install-headers:
	mkdir -p $(DESTDIR)$(INCLUDEDIR)
	cp -R --preserve=timestamps include/. $(DESTDIR)$(INCLUDEDIR)/.
 
install-kernel: nosense.kernel
	mkdir -p $(DESTDIR)$(BOOTDIR)
	cp nosense.kernel $(DESTDIR)$(BOOTDIR)
 
-include $(OBJS:.o=.d)