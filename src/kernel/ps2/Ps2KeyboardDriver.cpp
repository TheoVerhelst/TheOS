#include <kernel/ps2/Ps2KeyboardDriver.hpp>
#include <Printer.hpp>

namespace ps2
{

Ps2KeyboardDriver keyboardDriver;

void Ps2KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte))
	{
		_bufferEnd = _bufferEnd + 1 >= _bufferSize ? _bufferSize : _bufferEnd + 1;
		_scanCodeBuffer[_bufferEnd] = byte;
	}
}

bool Ps2KeyboardDriver::isBufferEmpty()
{
	return _bufferEnd == 0;
}

void Ps2KeyboardDriver::flushBuffer()
{
	for(size_t i{0}; i < _bufferEnd; ++i)
		out << _scanCodeBuffer[i] << ".";
	_bufferEnd = 0;
}

}// namespace ps2
