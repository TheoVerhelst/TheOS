#include <kernel/ps2/KeyboardDriver.hpp>
#include <Printer.hpp>

namespace ps2
{

KeyboardDriver keyboardDriver;

void KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte) and _bufferEnd + 1 < _bufferSize)
		_buffer[_bufferEnd++] = byte;
}

bool KeyboardDriver::isBufferEmpty()
{
	return _bufferEnd == 0;
}

void KeyboardDriver::flushBuffer()
{
	for(size_t i{0}; i < _bufferEnd; ++i)
		if(not (_buffer[i] & 0x80))
			out << _buffer[i] << ".";
	_bufferEnd = 0;
}

}// namespace ps2
