#!/bin/sh
set -e
. ./iso.sh
 
qemu-system-$(utils/target-triplet-to-arch.sh $HOST) -cdrom nosense.iso