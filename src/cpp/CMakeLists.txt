set(SOURCES
	"mem.cpp"
	"new.cpp"
	"Printer.cpp"
	"string.cpp"
)

if(BUILD_TEST)
	add_library(cppTest OBJECT ${SOURCES})
else(BUILD_TEST)
	add_library(cpp OBJECT ${SOURCES})
endif(BUILD_TEST)
