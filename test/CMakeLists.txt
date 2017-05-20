set(TEST_SOURCE_FILES
    "cpp/allocators/MemoryManagerTest.cpp"
    "cpp/allocators/PoolAllocatorTest.cpp"
    "cpp/containers/ArrayTest.cpp"
    "cpp/containers/ListTest.cpp"
    "cpp/BitSetTest.cpp"
    "cpp/mathTest.cpp"
    "cpp/stringTest.cpp"
    "main.cpp"
    "StandardTerminal.cpp"
)

# Add another include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(BUILD_TEST TRUE)

add_subdirectory(../src/cpp buildCppTest)

set(TEST_EXECUTABLE_NAME "${PROJECT_NAME}Test")
add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES} $<TARGET_OBJECTS:cppTest>)

if(NOT SKIP_TEST)
    # Execute tests after the build
    add_custom_command(TARGET ${TEST_EXECUTABLE_NAME} POST_BUILD
        COMMAND "${CMAKE_BINARY_DIR}/${TEST_EXECUTABLE_NAME}"
    )
endif(NOT SKIP_TEST)
