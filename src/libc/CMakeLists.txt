set(SOURCES
	"string/memset.cpp"
	"string/memcpy.cpp"
	"string/strlen.cpp"
	"string/strcpy.cpp"
	"string/strrchr.cpp")

add_library(libc OBJECT ${SOURCES})
