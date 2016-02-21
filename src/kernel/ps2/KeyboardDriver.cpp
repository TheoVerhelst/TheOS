#include <Printer.hpp>
#include <kernel/ps2/Key.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

namespace ps2
{

KeyboardDriver keyboardDriver;

void KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte))
	{
		_currentSequence._scancodes[++_currentSequence._length] = byte;
		KeyEvent event{_mapper.get(_currentSequence)};
		// If the current scancode is a valid one
		if(event._key != Key::Unknown)
		{
			_eventQueue.pushBack(event);
			_currentSequence._length = 0;
		}
	}
}

bool KeyboardDriver::pendingEvent()
{
	return not _eventQueue.empty();
}

KeyEvent KeyboardDriver::getEvent()
{
	KeyEvent res{_eventQueue.back()};
	_eventQueue.popBack();
	return res;
}

}// namespace ps2
