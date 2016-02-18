#ifndef ISRDISPATCHER_HPP
#define ISRDISPATCHER_HPP

extern "C" void isrDispatcher(uint32_t gs, uint32_t fs, uint32_t es,
		uint32_t ds, uint32_t interruptNumber, uint32_t errorCode, uint32_t eip,
		uint32_t cs, uint32_t eflags, uint32_t useresp, uint32_t ss);

#endif// ISRDISPATCHER_HPP
