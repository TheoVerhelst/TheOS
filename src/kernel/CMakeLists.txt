set(SOURCES
	"GDT.cpp"
	"GDT.asm"
	"terminal/Terminal.cpp"
	"video/VGA_management.cpp"
	)

add_library(kernel OBJECT ${SOURCES})

