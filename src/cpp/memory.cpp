#include <memory.hpp>
#include <kernel/Kernel.hpp>
#include <Printer.hpp>

void* memcpy(void* dest, const void* src, size_t count)
{
	// Decompose into 32-bit blocks and 8-bit blocks so transfer may be faster
	size_t dword_blocks = count / sizeof(uint32_t),
	       byte_blocks = count % sizeof(uint32_t),
	       i;

	const uint32_t *dword_src = (const uint32_t *)(src);
	uint32_t *dword_dest = (uint32_t *)(dest);
	const uint8_t *byte_src = (const uint8_t *)(dword_src[dword_blocks]);
	uint8_t *byte_dest = (uint8_t *)(dword_dest[dword_blocks]);

	for(i = 0; i < dword_blocks; ++i)
		dword_dest[i] = dword_src[i];
	for(i = 0; i < byte_blocks; ++i)
		byte_dest[i] = byte_src[i];
	return dest;
}

extern "C" void memset(void* dest, char value, size_t count)
{
	char* castedDest{static_cast<char*>(dest)};
	for(size_t i{0}; i < count; ++i)
		castedDest[i] = value;
}

void memset(void* dest, uint16_t value, size_t count)
{
	uint16_t* castedDest{static_cast<uint16_t*>(dest)};
	for(size_t i{0}; i < count; ++i)
		castedDest[i] = value;
}

void* operator new(size_t size) throw()
{
	return static_cast<void*>(kernel.getHeapManager().allocate(size));
}

void operator delete(void* address) throw()
{
	kernel.getHeapManager().deallocate(static_cast<Byte*>(address));
}

void operator delete(void* address, size_t size) throw()
{
	kernel.getHeapManager().deallocate(static_cast<Byte*>(address), size);
}

void* operator new[](size_t size) throw()
{
	return ::operator new(size);
}

void operator delete[](void* address) throw()
{
	::operator delete(address);
}

void operator delete[](void* address, size_t size) throw()
{
	::operator delete(address, size);
}
