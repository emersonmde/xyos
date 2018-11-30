## Synopsis

XyOS is a very simple OS written in C.

I decided to start writing an OS kernel mostly just for fun and to learn how these low level functions work. I'd love to hear any advice or ideas on how I could improve it. I'm sure there's plenty of issues at the moment, but its a work in progress.

## Requirements

You need to be on linux in order to build the elf_i386 binary. Sadly I couldn't find a way to trick ld into working correctly on my Mac.

Build Requirements:
 - nasm
 - gcc/ld

Runtime Requirements:
 - qemu-system-i386, qemu-system-x86_64, or a bootloader like GRUB

## How to Run

 ```
$ make
$ qemu-system-x86_64 -kernel xyos
 ```

## Author

Matthew Emerson

## License

Released under MIT License.
