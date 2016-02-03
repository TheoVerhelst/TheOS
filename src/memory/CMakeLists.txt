set(SOURCES
	"GDT.cpp"
	"GDT.asm"
	"MemoryManager.cpp"
	)

add_library(memory OBJECT ${SOURCES})
