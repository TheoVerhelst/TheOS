set(MODULE_NAME "cppFreestanding")

list(TRANSFORM CPP_SOURCES PREPEND "../cpp/")

setupFreestanding()
add_library(${MODULE_NAME} STATIC ${CPP_SOURCES})
