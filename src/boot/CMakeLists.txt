set(SOURCES
	"boot.asm"
	"gdt.asm"
	"gdt.cpp"
	"Icxxabi.cpp"
	"kernelMain.cpp"
	"MemoryMap.cpp"
	"paging.cpp"
)

add_library(boot OBJECT ${SOURCES})
add_library(crti OBJECT "crti.asm")
add_library(crtn OBJECT "crtn.asm")
