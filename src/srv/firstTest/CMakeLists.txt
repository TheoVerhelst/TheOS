set(MODULE_NAME "firstTest")

set(SOURCES
    "main.asm"
    "function.cpp"
)

makeFreestanding("${MODULE_NAME}" "${SOURCES}")
target_link_libraries(${EXECUTABLE_NAME} gcc)
