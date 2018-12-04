include_directories("include/")

set(SERVER_NAME "firstTest")

set(SERVER_SOURCES
    "src/main.asm"
    "src/function.cpp"
)

add_library(firstTest OBJECT ${SERVER_SOURCES})

# Create the main executable
set(EXECUTABLE_NAME "${SERVER_NAME}.bin")
add_executable(${EXECUTABLE_NAME}
    "$<TARGET_OBJECTS:firstTest>"
)
