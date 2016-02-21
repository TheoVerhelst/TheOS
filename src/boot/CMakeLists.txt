set(SOURCES
	"kernelMain.cpp"
	"boot.asm"
	"Icxxabi.cpp"
	)

add_library(boot OBJECT ${SOURCES})

add_library(crti OBJECT "crti.asm")
add_library(crtn OBJECT "crtn.asm")
