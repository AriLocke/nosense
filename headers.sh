#!/bin/sh
set -e
. ./config.sh
 
mkdir -p "$SYSROOT"

for PROJECT in $SYSTEM_HEADER_PROJECTS; do
  (cd $PROJECT && DESTDIR="$SYSROOT" $MAKE install-headers)
done

 
cp -r lib "$SYSROOT""$INCLUDEDIR"