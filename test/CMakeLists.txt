set(TEST_SOURCE_FILES
    "main.cpp"
    "cpp/ArrayTest.cpp"
    "cpp/BitSetTest.cpp"
    "cpp/ListTest.cpp"
)

# Add another include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

set(TEST_EXECUTABLE_NAME "${PROJECT_NAME}Test")
add_executable(${TEST_EXECUTABLE_NAME} ${TEST_SOURCE_FILES})

# Execute tests after the build
add_custom_command(TARGET ${TEST_EXECUTABLE_NAME} POST_BUILD
    COMMAND "${CMAKE_BINARY_DIR}/${TEST_EXECUTABLE_NAME}"
)
