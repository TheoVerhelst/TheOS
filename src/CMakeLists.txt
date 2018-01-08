# Configure the assembly format
set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

# Add OS-build specific flags
set(CMAKE_CXX_COMPILER "/usr/local/cross/bin/i686-elf-g++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-exceptions -fno-rtti")

# Set up the linker
set(CRT_PATH "/usr/local/cross/lib/gcc/i686-elf/7.2.0")
set(CRTBEGIN_O "${CRT_PATH}/crtbegin.o")
set(CRTEND_O "${CRT_PATH}/crtend.o")
set(CONFIG_DIRECTORY "${PROJECT_SOURCE_DIR}/config")
set(CMAKE_CXX_LINK_FLAGS "-nostdlib -T ${CONFIG_DIRECTORY}/linker.ld")
# Some flags are set by default; disable them
set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

set(BUILD_TEST FALSE)

# List the main executable source files
add_subdirectory(boot)
add_subdirectory(kernel)
add_subdirectory(cpp)

# Create the main executable
set(EXECUTABLE_NAME "${PROJECT_NAME}.bin")
add_executable(${EXECUTABLE_NAME}
    "$<TARGET_OBJECTS:crti>"
    "${CRTBEGIN_O}"
    "$<TARGET_OBJECTS:boot>"
    "$<TARGET_OBJECTS:kernel>"
    "$<TARGET_OBJECTS:cpp>"
    "${CRTEND_O}"
    "$<TARGET_OBJECTS:crtn>"
)

target_link_libraries(${EXECUTABLE_NAME} gcc)

set(ISO_NAME "${PROJECT_NAME}.iso")
add_custom_target(${ISO_NAME} ALL
    # Make the iso file depend on the executable
    DEPENDS "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}"
    # Copy the iso directory structure
    COMMAND cp -r "${CONFIG_DIRECTORY}/iso/" "${CMAKE_BINARY_DIR}"
    # Put the .bin executable in the directory
    COMMAND cp "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}" "${CMAKE_BINARY_DIR}/iso/"
    # Create a new iso with grub
    COMMAND grub-mkrescue -o "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${ISO_NAME}" "${CMAKE_BINARY_DIR}/iso/"
    # Finally copy the run script
    COMMAND cp "${CONFIG_DIRECTORY}/run.py" "${CMAKE_BINARY_DIR}"
)
