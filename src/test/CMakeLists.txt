set(SOURCES
    "cpp/allocators/MemoryManagerTest.cpp"
    "cpp/allocators/PoolAllocatorTest.cpp"
    "cpp/containers/ArrayTest.cpp"
    "cpp/containers/ListTest.cpp"
    "cpp/containers/StaticQueueTest.cpp"
    "cpp/BitSetTest.cpp"
    "cpp/flagsTest.cpp"
    "cpp/mathTest.cpp"
    "cpp/stringTest.cpp"
    "main.cpp"
    "StandardTerminal.cpp"
)

set(EXECUTABLE_NAME "${PROJECT_NAME}Test")
add_executable(${EXECUTABLE_NAME} ${SOURCES})
target_link_libraries(${EXECUTABLE_NAME} cpp)

if(NOT SKIP_TEST)
    # Execute tests after the build
    add_custom_command(TARGET ${EXECUTABLE_NAME} POST_BUILD
        COMMAND "${CMAKE_BINARY_DIR}/${EXECUTABLE_NAME}"
    )
endif(NOT SKIP_TEST)
