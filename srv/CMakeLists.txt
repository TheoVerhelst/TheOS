# Configure the assembly format
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

# Add OS-build specific flags
set(CMAKE_CXX_COMPILER "/usr/local/cross/bin/i686-elf-g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-exceptions -fno-rtti")

# Set up the linker
set(CRT_PATH "/usr/local/cross/lib/gcc/i686-elf/7.2.0")
set(CRTBEGIN_O "${CRT_PATH}/crtbegin.o")
set(CRTEND_O "${CRT_PATH}/crtend.o")
set(CMAKE_CXX_LINK_FLAGS "-nostdlib")
# Some flags are set by default; disable them
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

# Add all server directories
add_subdirectory(firstTest)
