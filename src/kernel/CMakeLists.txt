set(SOURCES
	"interrupts/idt.cpp"
	"interrupts/interruptHandler.asm"
	"interrupts/isr.cpp"
	"interrupts/pic.cpp"
	"memory/paging/bootstrap.cpp"
	"memory/paging/PageTableManager.cpp"
	"memory/paging/paging.cpp"
	"memory/paging/PhysicalMemoryManager.cpp"
	"ps2/Driver.cpp"
	"ps2/KeyboardDriver.cpp"
	"ps2/KeyEventMapper.cpp"
	"ps2/Scancode.cpp"
	"ps2/ScancodeMapper.cpp"
	"terminal/KernelTerminal.cpp"
	"video/vgaManagement.cpp"
	"gdt.asm"
	"gdt.cpp"
	"io.cpp"
	"Kernel.cpp"
)

foreach(INDEX RANGE 63)
	set(SOURCES "${SOURCES}"
		"interrupts/isr/asm/isr${INDEX}.asm"
		"interrupts/isr/cpp/isr${INDEX}.cpp"
	)
endforeach(INDEX)

add_library(kernel OBJECT ${SOURCES})
