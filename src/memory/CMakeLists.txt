set(SOURCES
	"GDT.cpp"
	"GDT.asm"
	)

add_library(memory OBJECT ${SOURCES})
