#ifndef ISRDISPATCHER_HPP
#define ISRDISPATCHER_HPP

#include <cstdint>

struct ErrorCode
{
	uint8_t externalEvent:1;
	uint8_t descriptorLocation:1;
	uint8_t gdtLdt:1;
	uint16_t segmentSelectorIndex:13;
	uint16_t reserved;
} __attribute__((packed));
static_assert(sizeof(ErrorCode) == 4, "Error code structure must be 32-bit");

extern "C" void isrDispatcher(uint32_t gs, uint32_t fs, uint32_t es,
		uint32_t ds, uint32_t interruptNumber, ErrorCode errorCode, uint32_t eip,
		uint32_t cs, uint32_t eflags, uint32_t useresp, uint32_t ss);

#endif// ISRDISPATCHER_HPP
