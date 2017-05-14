#include <kernel/ps2/KeyEventMapper.hpp>
#include <cpp/log.hpp>

namespace ps2
{

KeyEventMapper::KeyEventMapper(Mapping mapping):
	_currentMapping{mapping}
{
	STOP();
}

void KeyEventMapper::registerEvent(const KeyEvent& event)
{
	if(event._pressed)
	{
		const size_t mappingIndex{static_cast<size_t>(_currentMapping)};
		for(const auto& mapping : _mappings[mappingIndex])
		{
			if(mapping._key == event._key and isEventSatisfied(mapping))
			{
				_characterQueue.pushBack(mapping._character);
				return;
			}
		}
	}
	switch(event._key)
	{
		case Key::LAlt:
			_lAltPressed = event._pressed;
			break;

		case Key::RAlt:
			_rAltPressed = event._pressed;
			break;

		case Key::LControl:
			_lControlPressed = event._pressed;
			break;

		case Key::RControl:
			_rControlPressed = event._pressed;
			break;

		case Key::LShift:
			_lShiftPressed = event._pressed;
			break;

		case Key::RShift:
			_rShiftPressed = event._pressed;
			break;

		case Key::CapsLock:
			if(event._pressed)
				_capsLocked = not _capsLocked;
			break;

		default:
			break;
	}
}

bool KeyEventMapper::pendingCharacter() const
{
	return not _characterQueue.empty();
}

KeyEventMapper::Character KeyEventMapper::getCharacter()
{
	return _characterQueue.popFront();
}

bool KeyEventMapper::isEventSatisfied(const KeyEventMapping& event) const
{
	return ((event._altNeeded and (_lAltPressed or _rAltPressed)) or (not event._altNeeded and not (_lAltPressed or _rAltPressed)))
			and ((event._shiftNeeded and (_lShiftPressed or _rShiftPressed or _capsLocked)) or (not event._shiftNeeded and not (_lShiftPressed or _rShiftPressed or _capsLocked)));
}

const KeyEventMapper::KeyEventMapping KeyEventMapper::_mappings[][KeyEventMapper::_keyEventMappingNumber] =
{
	{
	},
	{
	},
	{
		{Key::BackSpace, '\b', false, false},
		{Key::Tab, '\t', false, false},
		{Key::Return, '\n', false, false},
		{Key::Slash, '\x15', true, false},// The § character
		{Key::Space, ' ', false, false},
		{Key::Slash, '!', false, false},
		{Key::Num3, '"', false, false},
		{Key::Num3, '#', false, true},
		{Key::RBracket, '$', false, false},
		{Key::Quote, '%', true, false},
		{Key::Num1, '&', false, false},
		{Key::Num4, '\'', false, false},
		{Key::Num5, '(', false, false},
		{Key::Dash, ')', false, false},
		{Key::BackSlash, '*', false, false},
		{Key::Equal, '+', true, false},
		{Key::M, ',', false, false},
		{Key::Num6, '-', false, false},
		{Key::Comma, '.', true, false},
		{Key::Period, '/', true, false},
		{Key::Num0, '0', true, false},
		{Key::Num1, '1', true, false},
		{Key::Num2, '2', true, false},
		{Key::Num3, '3', true, false},
		{Key::Num4, '4', true, false},
		{Key::Num5, '5', true, false},
		{Key::Num6, '6', true, false},
		{Key::Num7, '7', true, false},
		{Key::Num8, '8', true, false},
		{Key::Num9, '9', true, false},
		{Key::Period, ':', false, false},
		{Key::Comma, ';', false, false},
		{Key::LeftOfZ, '<', false, false},
		{Key::Equal, '=', false, false},
		{Key::LeftOfZ, '>', true, false},
		{Key::M, '?', true, false},
		{Key::Num0, '@', false, true},
		{Key::Q, 'A', true, false},
		{Key::B, 'B', true, false},
		{Key::C, 'C', true, false},
		{Key::D, 'D', true, false},
		{Key::E, 'E', true, false},
		{Key::F, 'F', true, false},
		{Key::G, 'G', true, false},
		{Key::H, 'H', true, false},
		{Key::I, 'I', true, false},
		{Key::J, 'J', true, false},
		{Key::K, 'K', true, false},
		{Key::L, 'L', true, false},
		{Key::SemiColon, 'M', true, false},
		{Key::N, 'N', true, false},
		{Key::O, 'O', true, false},
		{Key::P, 'P', true, false},
		{Key::A, 'Q', true, false},
		{Key::R, 'R', true, false},
		{Key::S, 'S', true, false},
		{Key::T, 'T', true, false},
		{Key::U, 'U', true, false},
		{Key::V, 'V', true, false},
		{Key::Z, 'W', true, false},
		{Key::X, 'X', true, false},
		{Key::Y, 'Y', true, false},
		{Key::W, 'Z', true, false},
		{Key::Num5, '[', false, true},
		{Key::Num8, '\\', false, true},
		{Key::Dash, ']', false, true},
		{Key::Num9, '^', false, true},
		{Key::Num8, '_', false, false},
		{Key::Num7, '`', false, true},
		{Key::Q, 'a', false, false},
		{Key::B, 'b', false, false},
		{Key::C, 'c', false, false},
		{Key::D, 'd', false, false},
		{Key::E, 'e', false, false},
		{Key::F, 'f', false, false},
		{Key::G, 'g', false, false},
		{Key::H, 'h', false, false},
		{Key::I, 'i', false, false},
		{Key::J, 'j', false, false},
		{Key::K, 'k', false, false},
		{Key::L, 'l', false, false},
		{Key::SemiColon, 'm', false, false},
		{Key::N, 'n', false, false},
		{Key::O, 'o', false, false},
		{Key::P, 'p', false, false},
		{Key::A, 'q', false, false},
		{Key::R, 'r', false, false},
		{Key::S, 's', false, false},
		{Key::T, 't', false, false},
		{Key::U, 'u', false, false},
		{Key::V, 'v', false, false},
		{Key::Z, 'w', false, false},
		{Key::X, 'x', false, false},
		{Key::Y, 'y', false, false},
		{Key::W, 'z', false, false},
		{Key::Num4, '{', false, true},
		{Key::Num6, '|', false, true},
		{Key::Equal, '}', false, true},
		{Key::Num2, '~', false, true},
		{Key::Num2, '\x82', false, false},// The é character
		{Key::Num0, '\x85', false, false},// The à character
		{Key::Num9, '\x87', false, false},// The ç character
		{Key::Num7, '\x8A', false, false},// The è character
		{Key::Quote, '\x97', false, false},// The ù character
		{Key::RBracket, '\x9C', true, false},// The £ character
		{Key::BackSlash, '\xE6', true, false},// The µ character
		{Key::Dash, '\xF8', true, false},// The ù character
		{Key::BackTick, '\xFD', false, false}// The square (power) character
	},
	{
	}
};

}// namespace ps2
