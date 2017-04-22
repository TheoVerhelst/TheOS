#include <string.hpp>

extern "C"
{

void *memset(void *address, int value, size_t bytes)
{
	return _memset(address, (unsigned char)value, bytes);
}

}// extern "C"

void *_memset(void *address, uint8_t value, size_t bytes)
{
	size_t i;
	uint8_t *byte_array = (uint8_t *)(address);

	for(i = 0; i < bytes; ++i)
		byte_array[i] = value&0xFF;

	return address;
}

void *_memset(void *address, uint16_t value, size_t blocks)
{
	size_t i;
	uint16_t *word_array = (uint16_t *)(address);

	for(i = 0; i < blocks; ++i)
		word_array[i] = value;

	return address;
}

void *_memset(void *address, uint32_t value, size_t blocks)
{
	size_t i;
	uint32_t *dword_array = (uint32_t *)(address);

	for(i = 0; i < blocks; ++i)
		dword_array[i] = value;

	return address;
}
