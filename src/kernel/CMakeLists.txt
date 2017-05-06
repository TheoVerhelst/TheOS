set(SOURCES
	"abort.cpp"
	"Kernel.cpp"
	"io.cpp"
	"memory/PhysicalMemoryManager.cpp"
	"memory/paging.cpp"
	"memory/MemoryManager.cpp"
	"terminal/KernelTerminal.cpp"
	"video/vgaManagement.cpp"
	"ps2/Driver.cpp"
	"ps2/KeyboardDriver.cpp"
	"ps2/ScancodeMapper.cpp"
	"ps2/KeyEventMapper.cpp"
	"ps2/Scancode.cpp"
	"gdt.cpp"
	"gdt.asm"
	"interrupts/idt.cpp"
	"interrupts/pic.cpp"
	"interrupts/interruptHandler.asm"
	"interrupts/isr.cpp"
)

foreach(INDEX RANGE 63)
	set(SOURCES "${SOURCES}"
		"interrupts/isr/asm/isr${INDEX}.asm"
		"interrupts/isr/cpp/isr${INDEX}.cpp"
	)
endforeach(INDEX)

add_library(kernel OBJECT ${SOURCES})
