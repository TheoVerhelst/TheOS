# TheOS

TheOS is an operating system written in C++ for learning purposes, forked from
BermudOS.

## Some explanations
This self-proclaimed kernel uses GRUB as bootloader, and uses GCC cross-compiled
for i686 plateform. The source files are organized as follow:
 * `src/` contains the `.cpp` and `.asm` source files
 * `include/` contains the `.hpp` header files
 * `{src|include}/kernel/` contains all the actual stuff directly related to the
 kernel
 * `{src|include}/cpp/` contains implementation of missing C++ features due to
 freestanding compilation (the whole standard library, for example)
 * `{src|include}/std/` contains headers directly copied from my system C++
 header files, which cover functionalities that are too complex to implement
 myself (such as `<limits>`, or `<type_traits>`)
 * `test/` contains unit tests, using the Catch library.

Note that due to the inherent nature of kernel code, it is impossible to unit-test the content of the `kernel/` directories. This is why it is separated from the `cpp/` directories, the latter being easily testable.

## Requirements
 * CMake >= 3.2
 * i686-elf-g++ >= 6.2 (gcc cross-compiled for i686-elf plateform)
 * nasm
 * grub-mkrescue
 * [Catch >= 1.9.3](https://github.com/philsquared/Catch/releases/download/v1.9.3/catch.hpp)

## Installation & run
Copy the `catch.hpp` file from Catch into `test/catch`.
Then run

    mkdir build && cd build
	cmake ..
	make
	./run.sh
