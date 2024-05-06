#!/bin/sh
set -e
. ./build.sh

mkdir -p iso_root
mkdir -p iso_root/boot
mkdir -p iso_root/boot/grub

cp sysroot/boot/nosense.kernel iso_root/boot/nosense.kernel
 
cat > iso_root/boot/grub/grub.cfg << EOF
menuentry "nosense" {
    multiboot /boot/nosense.kernel
}
EOF
grub-mkrescue -o nosense.iso iso_root
