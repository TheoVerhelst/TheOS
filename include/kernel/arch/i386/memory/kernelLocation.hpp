#ifndef KERNELLOCATION_HPP
#define KERNELLOCATION_HPP

/// Symbols located at precise places in the kernel image, allowing to retrieve
/// the position and size of the kernel in memory. The address of the variables
/// should be taken, not their values.
extern "C" void* kernelVirtualStart;
extern "C" void* kernelVirtualEnd;
extern "C" void* kernelPhysicalStart;
extern "C" void* kernelPhysicalEnd;
extern "C" void* lowKernelStart;
extern "C" void* lowKernelEnd;

/// The address of the end of the lower memory, i.e. the memory
/// before the 1Mo limit. Lower memory shouldn't be used, since only
/// a very short part is usable (about 640Ko).
constexpr uintptr_t lowerMemoryLimit{0x100000};

/// The offset between the physical and the logical location of the kernel in
/// the memory. This value is defined in the linker script, but we redefine it
/// here in order to be able to use it as a constexpr (such as for array
/// sizing).
constexpr size_t kernelVirtualOffset{0xC0000000};

#endif // KERNELLOCATION_HPP
