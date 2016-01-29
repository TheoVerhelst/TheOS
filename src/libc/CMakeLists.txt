set(SOURCES
	"stdio/printf.cpp"
	"stdio/putchar.cpp"
	"stdio/puts.cpp"
	"string/strlen.cpp"
	"string/strrchr.cpp")

add_library(libc ${SOURCES})

target_link_libraries(libc kernel io)

