#!/bin/sh

if [ -z "$1" ]; then
    echo "gen_grub_cfg.sh: Missing filename parameter"
    exit 1
fi

cat > $1 << EOF
set timeout=0
menuentry "XyOS" {
	multiboot /boot/xyos
}
EOF
