#include <kernel/ps2/Key.hpp>
#include <kernel/ps2/KeyboardDriver.hpp>

namespace ps2
{

void KeyboardDriver::pollKeyboard()
{
	uint8_t byte;
	if(read(byte) and _currentScancode.length < Scancode::maxLength)
	{
		_currentScancode.bytes[_currentScancode.length++] = byte;
		KeyEvent event{_scancodeMapper.get(_currentScancode)};
		// If the current scancode is a valid one
		if(event.key != Key::Unknown)
		{
			_keyEventMapper.registerEvent(event);
			_currentScancode.length = 0;
		}
	}
}

bool KeyboardDriver::characterQueueEmpty()
{
	return _keyEventMapper.characterQueueEmpty();
}

char KeyboardDriver::getCharacter()
{
	if(not characterQueueEmpty())
		return _keyEventMapper.getCharacter();
	else
		return '\0';
}

} // namespace ps2
