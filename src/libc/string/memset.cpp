#include <string.hpp>

void *memsetb(void *address, uint8_t value, size_t bytes)
{
	size_t i;
	uint8_t *byte_array = (uint8_t *)(address);

	for(i = 0; i < bytes; ++i)
		byte_array[i] = value&0xFF;

	return address;
}

void *memsetw(void *address, uint16_t value, size_t blocks)
{
	size_t i;
	uint16_t *word_array = (uint16_t *)(address);

	for(i = 0; i < blocks; ++i)
		word_array[i] = value;

	return address;
}

void *memsetd(void *address, uint32_t value, size_t blocks)
{
	size_t i;
	uint32_t *dword_array = (uint32_t *)(address);

	for(i = 0; i < blocks; ++i)
		dword_array[i] = value;

	return address;
}

