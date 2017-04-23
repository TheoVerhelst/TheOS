#include <memory.hpp>
#include <kernel/Kernel.hpp>
#include <Printer.hpp>

void memcpy(void* dest, const void* src, size_t count)
{
	// Decompose into 32-bit blocks and 8-bit blocks so transfer may be faster
	size_t dwordCount{count / sizeof(uint32_t)};
	size_t byteCount{count % sizeof(uint32_t)};

	const uint32_t* dwordSrc{(const uint32_t*)(src)};
	uint32_t* dwordDest{(uint32_t*)(dest)};
	const uint8_t* byteSrc{(const uint8_t*)(dwordSrc + dwordCount)};
	uint8_t* byteDest{(uint8_t*)(dwordDest + dwordCount)};

	for(size_t i{0}; i < dwordCount; ++i)
		dwordDest[i] = dwordSrc[i];
	for(size_t i{0}; i < byteCount; ++i)
		byteDest[i] = byteSrc[i];
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
