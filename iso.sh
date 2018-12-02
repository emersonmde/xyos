#!/bin/sh
set -e
. ./build.sh

mkdir -p isodir
mkdir -p isodir/boot
mkdir -p isodir/boot/grub

cp sysroot/boot/xyos isodir/boot/xyos
cat > isodir/boot/grub/grub.cfg << EOF
set timeout=1
menuentry "XyOS" {
	multiboot /boot/xyos
}
EOF
grub-mkrescue -o xyos.iso isodir
