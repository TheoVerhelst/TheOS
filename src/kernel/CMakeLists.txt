set(SOURCES
	"terminal/Terminal.cpp"
	"video/VGA_management.cpp"
	)

add_library(kernel OBJECT ${SOURCES})

