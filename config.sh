#!/bin/sh
SYSTEM_HEADER_PROJECTS="libc kernel"
PROJECTS="libc kernel"
 
export MAKE=${MAKE:-make}
export HOST=${HOST:-$(utils/default-host.sh)}
 
export CC=~/opt/cross/bin/${HOST}-gcc # may need elf before -gcc
export LD="~/opt/cross/bin/${HOST}-gcc -T"
export AS=~/opt/cross/bin/${HOST}-gcc


export PREFIX=/usr
export EXEC_PREFIX=$PREFIX
export BOOTDIR=/boot
export LIBDIR=$EXEC_PREFIX/lib
export INCLUDEDIR=$PREFIX/include
 
export CFLAGS='-O2 -g'
export CPPFLAGS=''
 
# Configure the cross-compiler to use the desired system root.
export SYSROOT="$(pwd)/sysroot"
export CC="$CC --sysroot=$SYSROOT"
export LD="$LD --sysroot=$SYSROOT"
export AS="$AS --sysroot=$SYSROOT"
 
# Work around that the -elf gcc targets doesn't have a system include directory
# because it was configured with --without-headers rather than --with-sysroot.
if echo "$HOST" | grep -Eq -- '-elf($|-)'; then
  export CC="$CC -isystem=$INCLUDEDIR"
fi
