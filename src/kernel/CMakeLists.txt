set(SOURCES
	"memcpy.cpp"
	"memset.cpp"
	"terminal/terminal.cpp"
	"video/VGA_management.cpp"
	)

add_library(kernel ${SOURCES})

