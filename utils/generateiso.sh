#!/bin/sh
mkdir image
cd image
# Download the latest Limine binary release for the 7.x branch.
# git clone https://github.com/limine-bootloader/limine.git --branch=v7.x-binary --depth=1
 
# Build "limine" utility.
# make -C limine
 
# Create a directory which will be our ISO root.
mkdir -p iso_root
 
# Copy the relevant files over.
mkdir -p iso_root/boot
cp ../bin/nosense.kernel iso_root/boot/nosense.kernel

mkdir -p iso_root/boot/grub
 
cat > iso_root/boot/grub/grub.cfg << EOF
menuentry "nosense" {
	multiboot /boot/nosense.kernel
}
EOF
grub-mkrescue -o nosense.iso iso_root


# Install Limine stage 1 and 2 for legacy BIOS boot.
# ./limine/limine bios-install nosense.iso