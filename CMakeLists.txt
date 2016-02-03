cmake_minimum_required(VERSION 3.2)

set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

project(TheOS LANGUAGES CXX ASM_NASM)

#Set up the C++ compiler
set(CMAKE_CXX_COMPILER "i686-elf-g++")
set(CMAKE_CXX_FLAGS "-std=c++14 -ffreestanding -O0 -Wall -Wextra -fno-exceptions -fno-rtti")

#Set up the linker
#Path to crtbegin.o and crtend.o
set(CRT_PATH "/usr/local/cross/lib/gcc/i686-elf/5.3.0")
set(CRTBEGIN_O "${CRT_PATH}/crtbegin.o")
set(CRTEND_O "${CRT_PATH}/crtend.o")

#The linker configuration file
set(LINKER_FILE "${PROJECT_SOURCE_DIR}/config/linker.ld")

set(CMAKE_CXX_LINK_FLAGS "-nostdlib -T ${LINKER_FILE}")
#Some flags are set by default; disable them
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

#Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

#List the main executable source files
add_subdirectory(src/boot)
add_subdirectory(src/kernel)
add_subdirectory(src/io)
add_subdirectory(src/memory)
add_subdirectory(src/libc)
add_subdirectory(src/libc++)

#Create the main executable
add_executable(${PROJECT_NAME}.bin
	"$<TARGET_OBJECTS:crti>"
	"${CRTBEGIN_O}"
	"$<TARGET_OBJECTS:boot>"
	"$<TARGET_OBJECTS:kernel>"
	"$<TARGET_OBJECTS:io>"
	"$<TARGET_OBJECTS:memory>"
	"$<TARGET_OBJECTS:libc>"
	"$<TARGET_OBJECTS:libc++>"
	"${CRTEND_O}"
	"$<TARGET_OBJECTS:crtn>"
	)

target_link_libraries(${PROJECT_NAME}.bin gcc)

#Make the iso
file(COPY "${CMAKE_SOURCE_DIR}/iso" DESTINATION "${CMAKE_BINARY_DIR}")
#First, delete old iso
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	rm -f ${CMAKE_BINARY_DIR}/iso/boot/${PROJECT_NAME}.iso)
#Then copy the executable
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	cp ${PROJECT_NAME}.bin ${CMAKE_BINARY_DIR}/iso/boot/${PROJECT_NAME}.bin)
#Finaly create the iso with grub
add_custom_command(TARGET ${PROJECT_NAME}.bin POST_BUILD COMMAND
	grub-mkrescue -o ${PROJECT_NAME}.iso ${CMAKE_BINARY_DIR}/iso)

