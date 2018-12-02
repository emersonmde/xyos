## Synopsis

XyOS is a very simple OS kernel written in C.

I decided to start writing an OS kernel mostly just for fun and to learn how these low level functions work. I'd love to hear any advice or ideas on how I could improve it. I'm sure there's plenty of issues at the moment, but its a work in progress.

## Requirements

In order to build the i686-elf kernel, you need to have a GCC cross compiler for that target. Although the x86_64 GCC seems to build the kernel normally, this could lead to strange errors, bugs, and undefined behavior. The [GCC-Cross-Compiler](https://wiki.osdev.org/GCC_Cross-Compiler) article on wiki.osdev.org was super helpful into getting this working.

### Cross Compiling GCC with MacOS

Although some of the requirements for GCC are already installed, some are out of date and others don't support the needed features. The major requirements needed are:
 - gmp
 - mpfr
 - libmpc
 - libiconv
 - binutils

I was able to install all of these using [MacPorts](http://http//www.macports.org/):

```
sudo port install gmp mpfr libmpc libiconv
```

While compiling binutils seems to work using LLVM, when trying to compile gcc it would fail with errors (/usr/bin/gcc is actually an LLVM compiler). So install gcc with homebrew:

```
brew install gcc
```

Now download the source for [binutils](https://ftp.gnu.org/gnu/binutils/) and [gcc](http://mirrors-usa.go-parts.com/gcc/releases/):

```
mkdir -p $HOME/src
curl https://ftp.gnu.org/gnu/binutils/binutils-2.31.tar.gz >> $HOME/src/binutils-2.31.tar.gz
curl http://mirrors-usa.go-parts.com/gcc/releases/gcc-8.2.0/gcc-8.2.0.tar.gz >> $HOME/src/gcc-8.2.0.tar.gz
cd $HOME/src
tar -zxf binutils-2.31.tar.gz
tar -zxf gcc-8.2.0.tar.gz
```

Setup install directory and targets:

```
export PREFIX="/usr/local/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

Compile binutils:

```
mkdir $HOME/src/build-binutils
cd $HOME/src/build-binutils
../binutils-2.31/configure --prefix="$PREFIX" --target=$TARGET --enable-interwork --enable-multilib --disable-nls --disable-werror
make
sudo make install
```

Set real GCC as the compiler for building the GCC cross compiler:

```
export CC=/usr/local/bin/gcc-8
export CXX=/usr/local/bin/g++-8
export CPP=/usr/local/bin/cpp-8
export LD=/usr/local/bin/gcc-8
```

Compile GCC

```
mkdir $HOME/build-gcc
cd $HOME/build-gcc
../gcc-8.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers --enable-interwork --enable-multilib --with-gmp=/usr --with-mpc=/opt/local --with-mpfr=/opt/local
make all-gcc
make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc
```

Add the cross compiler tools to your path:

```
export PATH="/usr/local/cross/bin:$PATH"
```

### Cross Compiling GCC with Linux (Arch)

Download sources for binutils and GCC

```
mkdir -p $HOME/src
curl https://ftp.gnu.org/gnu/binutils/binutils-2.31.tar.gz >> $HOME/src/binutils-2.31.tar.gz
curl http://mirrors-usa.go-parts.com/gcc/releases/gcc-8.2.0/gcc-8.2.0.tar.gz >> $HOME/src/gcc-8.2.0.tar.gz
cd $HOME/src
tar -zxf binutils-2.31.tar.gz
tar -zxf gcc-8.2.0.tar.gz
```

Setup install directory and targets:

```
export PREFIX="/usr/local/cross"
export TARGET=i686-elf
export PATH="$PREFIX/bin:$PATH"
```

Compile binutils:

```
mkdir $HOME/src/build-binutils
cd $HOME/src/build-binutils
../binutils-2.31/configure --target=$TARGET --prefix="$PREFIX" --with-sysroot --disable-nls --disable-werror
make
sudo make install
```

Make sure i686-elf-as is installed (it was already installed on Arch):

```
which -- $TARGET-as || echo $TARGET-as is not in the PATH
```

If so, compile GCC:

```
mkdir $HOME/build-gcc
cd $HOME/build-gcc
../gcc-8.2.0/configure --target=$TARGET --prefix="$PREFIX" --disable-nls --enable-languages=c,c++ --without-headers
make all-gcc
make all-target-libgcc
sudo make install-gcc
sudo make install-target-libgcc
```

Add the cross compiler tools to your path:

```
export PATH="/usr/local/cross/bin:$PATH"
```

## Testing

### Using qemu

 ```
qemu-system-i386 -kernel xyos
 ```

## Author

Matthew Emerson

## License

Released under MIT License.
