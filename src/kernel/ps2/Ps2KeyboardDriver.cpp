#include <kernel/ps2/Ps2KeyboardDriver.hpp>

namespace ps2
{

Ps2KeyboardDriver keyboardDriver;

void Ps2KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte))
		_scanCodeBuffer.pushBack(byte);
}

bool Ps2KeyboardDriver::isBufferEmpty()
{
	return _scanCodeBuffer.empty();
}

List<uint8_t> Ps2KeyboardDriver::flushBuffer()
{
	List<uint8_t> res(_scanCodeBuffer);
	_scanCodeBuffer.clear();
	return res;
}

}// namespace ps2
