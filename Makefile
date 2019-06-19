SYSTEM_HEADER_PROJECTS=libc \
					   kernel

PROJECTS=libc \
		 kernel

MAKEFILE_PATH:=$(abspath $(lastword $(MAKEFILE_LIST)))
export CURRENTDIR:=$(patsubst %/,%,$(dir $(MAKEFILE_PATH)))

export HOST=i686-elf

export AR:=$(HOST)-ar
export AS:=$(HOST)-as
CC:=$(HOST)-gcc
MKDIR_P = mkdir -p

export CFLAGS=-O2 -g
export CPPFLAGS?=

export PREFIX=/usr
export EXEC_PREFIX:=$(PREFIX)
export BOOTDIR=/boot
export LIBDIR:=$(EXEC_PREFIX)/lib
export INCLUDEDIR:=$(PREFIX)/include
export SYSROOT:="$(CURRENTDIR)/sysroot"
export SCRIPTDIR:="$(CURRENTDIR)/scripts"
ISODIR:=$(CURRENTDIR)/iso
ISOBUILDDIR:=$(CURRENTDIR)/isobuild

export CC:=$(CC) --sysroot=$(SYSROOT) -isystem=$(INCLUDEDIR)

.PHONY: all headers build iso qemu clean

all: qemu

headers:
	$(MKDIR_P) $(SYSROOT)
	for PROJECT in $(SYSTEM_HEADER_PROJECTS) ; do \
		cd $(CURRENTDIR)/$$PROJECT && DESTDIR=$(SYSROOT) $(MAKE) install-headers ; \
	done

build: headers
	for PROJECT in $(PROJECTS) ; do \
		cd $(CURRENTDIR)/$$PROJECT && DESTDIR=$(SYSROOT) $(MAKE) install ; \
	done

iso: build
	$(MKDIR_P) $(ISOBUILDDIR)/boot/grub
	$(MKDIR_P) $(ISODIR)
	cp $(SYSROOT)/boot/xyos $(ISOBUILDDIR)/boot/xyos
	$(SCRIPTDIR)/gen_grub_cfg.sh $(ISOBUILDDIR)/boot/grub/grub.cfg
	grub-mkrescue -o $(ISODIR)/xyos.iso $(ISOBUILDDIR)

qemu: HOSTARCH!=$(SCRIPTDIR)/target-triplet-to-arch.sh $(HOST)
qemu: iso
	qemu-system-$(HOSTARCH) -cdrom $(ISODIR)/xyos.iso

clean:
	for PROJECT in $(PROJECTS) ; do \
		cd $(CURRENTDIR)/$$PROJECT && $(MAKE) clean ; \
	done
	rm -rf $(SYSROOT)
	rm -rf $(ISODIR)
	rm -rf $(ISOBUILDDIR)
