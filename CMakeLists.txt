cmake_minimum_required(VERSION 3.13)

project(TheOS LANGUAGES CXX ASM_NASM)

# Add include directory
include_directories("${PROJECT_SOURCE_DIR}/include")

option(SKIP_TEST "True to skip unit tests after build")

# Add flags to the C++ compiler
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -Wall -Wextra -pedantic")
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "${CMAKE_CXX_FLAGS_RELEASE} -O3")
set(CMAKE_ASM_NASM_FLAGS "${CMAKE_ASM_NASM_FLAGS} -Wall -Werror")

# Place the executable files in the root directory instead of in test
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

set(CONFIG_DIRECTORY "${PROJECT_SOURCE_DIR}/config")
set(OUTPUT_BINARIES "${CMAKE_BINARY_DIR}/kernel.bin" "${CMAKE_BINARY_DIR}/firstTest.bin")

macro(setupFreestanding)
    # Add OS-build specific flags
    set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")
    set(CMAKE_CXX_COMPILER "/usr/local/cross/bin/i686-elf-g++")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-exceptions -fno-rtti")

    # Set up the linker
    set(CRT_PATH "/usr/local/cross/lib/gcc/i686-elf/7.2.0")
    set(CRTBEGIN_O "${CRT_PATH}/crtbegin.o")
    set(CRTEND_O "${CRT_PATH}/crtend.o")
    set(CMAKE_CXX_LINK_FLAGS "-nostdlib -T ${CONFIG_DIRECTORY}/linker.ld")
    # Some flags are set by default; disable them
    set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")
endmacro(setupFreestanding)

macro(makeFreestanding MODULE_NAME SOURCES)
    setupFreestanding()
    add_library(${MODULE_NAME} OBJECT ${SOURCES})
    add_library("${MODULE_NAME}Crti" OBJECT "${PROJECT_SOURCE_DIR}/src/kernel/arch/i386/boot/crti.asm")
    add_library("${MODULE_NAME}Crtn" OBJECT "${PROJECT_SOURCE_DIR}/src/kernel/arch/i386/boot/crtn.asm")

    # Create the main executable
    set(EXECUTABLE_NAME "${MODULE_NAME}.bin")
    add_executable(${EXECUTABLE_NAME}
        "$<TARGET_OBJECTS:${MODULE_NAME}Crti>"
        "${CRTBEGIN_O}"
        "$<TARGET_OBJECTS:${MODULE_NAME}>"
        "${CRTEND_O}"
        "$<TARGET_OBJECTS:${MODULE_NAME}Crtn>"
    )
    target_link_libraries(${EXECUTABLE_NAME} gcc)
endmacro(makeFreestanding)

add_subdirectory(src)

add_custom_target("${PROJECT_NAME}.iso" ALL
    # Make the iso file depend on the kernel executable
    DEPENDS ${OUTPUT_BINARIES}
    # Copy the iso directory structure
    COMMAND cp -r "${CONFIG_DIRECTORY}/iso/" "${CMAKE_BINARY_DIR}"
    # Put the .bin executable in the directory
    COMMAND cp ${OUTPUT_BINARIES} "${CMAKE_BINARY_DIR}/iso/"
    # Create a new iso with grub
    COMMAND grub-mkrescue -o "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${PROJECT_NAME}.iso" "${CMAKE_BINARY_DIR}/iso/"
    # Finally copy the run script
    COMMAND cp "${CONFIG_DIRECTORY}/run.py" "${CMAKE_BINARY_DIR}"
)
