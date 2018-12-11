set(MODULE_NAME "cpp")

set(SOURCES
	"allocators/MemoryManager.cpp"
	"abort.cpp"
	"assert.cpp"
	"log.cpp"
	"mem.cpp"
	"new.cpp"
	"Printer.cpp"
	"string.cpp"
)

add_library(${MODULE_NAME} STATIC ${SOURCES})

# Make the CPP sources available to parent scope, to use by cppFreestanding
set(CPP_SOURCES ${SOURCES} PARENT_SCOPE)
