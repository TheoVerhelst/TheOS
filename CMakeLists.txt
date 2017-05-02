cmake_minimum_required(VERSION 3.2)

project(TheOS LANGUAGES CXX ASM_NASM)

option(BUILD_TEST "TRUE to build the unit tests" FALSE)

# Add include directory
include_directories("${PROJECT_SOURCE_DIR}/include")

# Add flags to the C++ compiler
set(CMAKE_CXX_FLAGS "-std=c++14 -Wall -Wextra")
set(CMAKE_CXX_FLAGS_DEBUG "-O0 -g")
set(CMAKE_CXX_FLAGS_RELEASE "-O3")

if(BUILD_TEST)
	add_subdirectory(test)
else(BUILD_TEST)
	set(CMAKE_ASM_NASM_OBJECT_FORMAT "elf32")

	# Add OS-build specific flags
	set(CMAKE_CXX_COMPILER "i686-elf-g++")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -ffreestanding -fno-exceptions -fno-rtti")

	# Set up the linker
	set(CRT_PATH "/usr/local/cross/lib/gcc/i686-elf/6.2.0")
	set(CRTBEGIN_O "${CRT_PATH}/crtbegin.o")
	set(CRTEND_O "${CRT_PATH}/crtend.o")
	set(CONFIG_DIRECTORY "${PROJECT_SOURCE_DIR}/config")
	set(CMAKE_CXX_LINK_FLAGS "-nostdlib -T ${CONFIG_DIRECTORY}/linker.ld")
	# Some flags are set by default; disable them
	set(CMAKE_SHARED_LIBRARY_LINK_CXX_FLAGS "")

	# List the main executable source files
	add_subdirectory(src/boot)
	add_subdirectory(src/kernel)
	add_subdirectory(src/cpp)

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

	add_custom_command(TARGET "${PROJECT_NAME}.bin" POST_BUILD
		COMMAND cp -r "${CONFIG_DIRECTORY}/iso/" "${CMAKE_BINARY_DIR}"
		COMMAND cp "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}" "${CMAKE_BINARY_DIR}/iso/"
		# Create a new iso with grub
		COMMAND grub-mkrescue -o "${PROJECT_NAME}.iso" "${CMAKE_BINARY_DIR}/iso/"
		# Finally copy the run script
		COMMAND cp "${CONFIG_DIRECTORY}/run.sh" "${CMAKE_BINARY_DIR}")
endif(BUILD_TEST)
