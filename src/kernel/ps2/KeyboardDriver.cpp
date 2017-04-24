#include <kernel/ps2/Key.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

namespace ps2
{

void KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte) and _currentScancode._length + 1 <= Scancode::_maxLength)
	{
		_currentScancode._bytes[_currentScancode._length++] = byte;
		KeyEvent event{_scancodeMapper.get(_currentScancode)};
		// If the current scancode is a valid one
		if(event._key != Key::Unknown)
		{
			_keyEventMapper.registerEvent(event);
			_currentScancode._length = 0;
		}
	}
}

bool KeyboardDriver::pendingCharacter()
{
	return _keyEventMapper.pendingCharacter();
}

char KeyboardDriver::getCharacter()
{
	if(pendingCharacter())
		return _keyEventMapper.getCharacter();
	else
		return '\0';
}

}// namespace ps2
