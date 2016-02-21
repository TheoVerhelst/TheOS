#include <kernel/ps2/Ps2KeyboardDriver.hpp>
#include <Printer.hpp>

namespace ps2
{

Ps2KeyboardDriver keyboardDriver;

void Ps2KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte) and _bufferEnd + 1 < _bufferSize)
		_buffer[_bufferEnd++] = byte;
}

bool Ps2KeyboardDriver::isBufferEmpty()
{
	return _bufferEnd == 0;
}

void Ps2KeyboardDriver::flushBuffer()
{
	for(size_t i{0}; i < _bufferEnd; ++i)
		if(not (_buffer[i] & 0x80))
			out << _buffer[i] << ".";
	_bufferEnd = 0;
}

}// namespace ps2
