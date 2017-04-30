# TheOS

TheOS is an operating system written in C++ for learning purposes, forked from
BermudOS.

## Why ?
See https://github.com/RobinPetit/BermudOS for rationale.

## Requirements
 * CMake >= 3.2
 * i686-elf-g++ >= 6.2 (cross-compiled gcc for i686-elf plateform)
 * nasm
 * grub-mkrescue
 * [Catch >= 1.9.3](https://github.com/philsquared/Catch/releases/download/v1.9.3/catch.hpp)

## Installation & run
Copy the `catch.hpp` file from Catch into `test/catch`

    mkdir build && cd build
	cmake ..
	make
	./run.sh
