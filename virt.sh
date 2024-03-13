#!/bin/sh
set -e
. ./iso.sh

virt-install --name nosense-vm \
--osinfo detect=on,require=off \
--vcpu 2 \
--memory 2048 \
--disk path=nosense.img,size=15 \
--graphics spice \
--cdrom nosense.iso \
--transient \
--noreboot \
--destroy-on-exit

#rm -rf os/nosense.img # ?
