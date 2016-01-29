cmake_minimum_required(VERSION 3.2)

set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

project(BermudOS LANGUAGES CXX ASM_NASM)

#Set up the C++ compiler
set(CMAKE_CXX_COMPILER "i686-elf-g++")
set(CMAKE_CXX_FLAGS "-ffreestanding -O2 -Wall -Wextra -fno-exceptions -fno-rtti")

#Set up the linker
set(LINKER_FILE "${PROJECT_SOURCE_DIR}/config/linker.ld")

set(CMAKE_CXX_LINK_FLAGS "-nostdlib -T ${LINKER_FILE}")
#Some flags are set by default; disable them
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

#Add include directory
include_directories(${PROJECT_SOURCE_DIR}/include)

#List the main executable source files
set(SOURCES
	"src/boot/kernel.cpp"
	"src/boot/boot.asm"
	)

#Create the main executable
add_executable(${PROJECT_NAME}.bin ${SOURCES})

add_subdirectory(src/kernel)
add_subdirectory(src/io)
add_subdirectory(src/libc)

#Add libraries
target_link_libraries(${PROJECT_NAME}.bin gcc kernel io libc)

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

