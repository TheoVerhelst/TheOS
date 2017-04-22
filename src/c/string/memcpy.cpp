#include <string.hpp>

extern "C"
{

void *memcpy(void *dest, const void *src, size_t bytes)
{
	// Decompose into 32-bit blocks and 8-bit blocks so transfer may be faster
	size_t dword_blocks = bytes / sizeof(uint32_t),
	       byte_blocks = bytes % sizeof(uint32_t),
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

}// extern "C"
