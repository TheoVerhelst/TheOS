# TheOS

TheOS is an operating system written in C++ for learning purposes, forked from
BermudOS.

## Why ?
See https://github.com/RobinPetit/BermudOS for rationale.

## Requirements
 * CMake 3.2 or higher
 * i686-elf-g++ 6.2 (cross-compiled gcc for i686-elf plateform)
 * nasm
 * grub-mkrescue

## Installation & run

    mkdir build && cd build
	cmake ..
	make
	./run.sh
