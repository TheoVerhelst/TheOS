set(TEST_SOURCE_FILES
    "main.cpp"
)

# Place the executable files in the root directory instead of in test
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

# Add another include directory
include_directories("${CMAKE_CURRENT_SOURCE_DIR}")

add_executable("${PROJECT_NAME}Test" ${TEST_SOURCE_FILES})
