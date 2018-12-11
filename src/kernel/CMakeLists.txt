set(MODULE_NAME "kernel")

set(SOURCES
	"arch/i386/boot/boot.asm"
	"arch/i386/boot/kernelMain.cpp"
	"arch/i386/interrupts/idt.cpp"
	"arch/i386/interrupts/interruptHandler.asm"
	"arch/i386/interrupts/isr.cpp"
	"arch/i386/interrupts/pic.cpp"
	"arch/i386/memory/paging/bootPaging.cpp"
	"arch/i386/memory/paging/PageTableManager.cpp"
	"arch/i386/memory/paging/paging.cpp"
	"arch/i386/memory/paging/PhysicalMemoryManager.cpp"
	"arch/i386/memory/segmentation/gdt.asm"
	"arch/i386/memory/segmentation/gdt.cpp"
	"multiboot/MemoryMap.cpp"
	"ps2/Driver.cpp"
	"ps2/KeyboardDriver.cpp"
	"ps2/KeyEventMapper.cpp"
	"ps2/ScancodeMapper.cpp"
	"vga/VgaTerminal.cpp"
	"vga/vgaManagement.cpp"
	"Icxxabi.cpp"
	"io.cpp"
	"Kernel.cpp"
)

foreach(INDEX RANGE 63)
	set(SOURCES "${SOURCES}"
		"arch/i386/interrupts/isr/asm/isr${INDEX}.asm"
		"arch/i386/interrupts/isr/cpp/isr${INDEX}.cpp"
	)
endforeach(INDEX)

makeFreestanding("${MODULE_NAME}" "${SOURCES}")
target_link_libraries("${MODULE_NAME}.bin" cppFreestanding gcc)
