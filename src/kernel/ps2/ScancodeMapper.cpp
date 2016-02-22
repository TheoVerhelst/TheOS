#include <kernel/ps2/ScancodeMapper.hpp>

namespace ps2
{

ScancodeMapper::ScancodeMapper(Mapping mapping):
	_currentMapping{mapping}
{
}

const KeyEvent& ScancodeMapper::get(const Scancode& scancode)
{
	// Some optimizations (don't loop over the whole mapping) with the fact that
	// the first byte is the escape byte iff length > 0
	//~const bool lenghtOne{scancode._length == 1};
	//~const bool firstIsEscape{scancode._bytes[0] == _escapeByte};
	//~if(lenghtOne and firstIsEscape)
		//~return _unknowEvent;
	//~else if(not lenghtOne and not firstIsEscape)
		//~return _unknowEvent;

	// Find out the first corresponding sequence
	const size_t mappingIndex{static_cast<size_t>(_currentMapping)};
	for(size_t i{0}; i < _scancodeMappingNumber; ++i)
		if(_mappings[mappingIndex][i]._scancode == scancode)
			return _mappings[mappingIndex][i]._keyEvent;
	return _unknowEvent;
}

ScancodeMapper::Mapping ScancodeMapper::getCurrentMapping() const
{
	return _currentMapping;
}

void ScancodeMapper::setCurrentMapping(Mapping newCurrentMapping)
{
	_currentMapping = newCurrentMapping;
}

constexpr KeyEvent ScancodeMapper::_unknowEvent;

const ScancodeMapper::ScancodeMapping ScancodeMapper::_mappings[][ScancodeMapper::_scancodeMappingNumber] =
{
	{
		{{1, {0x01}}, {Key::Escape, true}},
		{{1, {0x02}}, {Key::Num1, true}},
		{{1, {0x03}}, {Key::Num2, true}},
		{{1, {0x04}}, {Key::Num3, true}},
		{{1, {0x05}}, {Key::Num4, true}},
		{{1, {0x06}}, {Key::Num5, true}},
		{{1, {0x07}}, {Key::Num6, true}},
		{{1, {0x08}}, {Key::Num7, true}},
		{{1, {0x09}}, {Key::Num8, true}},
		{{1, {0x0A}}, {Key::Num9, true}},
		{{1, {0x0B}}, {Key::Num0, true}},
		{{1, {0x0C}}, {Key::Dash, true}},
		{{1, {0x0D}}, {Key::Equal, true}},
		{{1, {0x0E}}, {Key::BackSpace, true}},
		{{1, {0x0F}}, {Key::Tab, true}},
		{{1, {0x10}}, {Key::Q, true}},
		{{1, {0x11}}, {Key::W, true}},
		{{1, {0x12}}, {Key::E, true}},
		{{1, {0x13}}, {Key::R, true}},
		{{1, {0x14}}, {Key::T, true}},
		{{1, {0x15}}, {Key::Y, true}},
		{{1, {0x16}}, {Key::U, true}},
		{{1, {0x17}}, {Key::I, true}},
		{{1, {0x18}}, {Key::O, true}},
		{{1, {0x19}}, {Key::P, true}},
		{{1, {0x1A}}, {Key::LBracket, true}},
		{{1, {0x1B}}, {Key::RBracket, true}},
		{{1, {0x1C}}, {Key::Return, true}},
		{{1, {0x1D}}, {Key::LControl, true}},
		{{1, {0x1E}}, {Key::A, true}},
		{{1, {0x1F}}, {Key::S, true}},
		{{1, {0x20}}, {Key::D, true}},
		{{1, {0x21}}, {Key::F, true}},
		{{1, {0x22}}, {Key::G, true}},
		{{1, {0x23}}, {Key::H, true}},
		{{1, {0x24}}, {Key::J, true}},
		{{1, {0x25}}, {Key::K, true}},
		{{1, {0x26}}, {Key::L, true}},
		{{1, {0x27}}, {Key::SemiColon, true}},
		{{1, {0x28}}, {Key::Quote, true}},
		{{1, {0x29}}, {Key::Tilde, true}},
		{{1, {0x2A}}, {Key::LShift, true}},
		{{1, {0x2B}}, {Key::BackSlash, true}},
		{{1, {0x2C}}, {Key::Z, true}},
		{{1, {0x2D}}, {Key::X, true}},
		{{1, {0x2E}}, {Key::C, true}},
		{{1, {0x2F}}, {Key::V, true}},
		{{1, {0x30}}, {Key::B, true}},
		{{1, {0x31}}, {Key::N, true}},
		{{1, {0x32}}, {Key::M, true}},
		{{1, {0x33}}, {Key::Comma, true}},
		{{1, {0x34}}, {Key::Period, true}},
		{{1, {0x35}}, {Key::Slash, true}},
		{{1, {0x36}}, {Key::RShift, true}},
		{{1, {0x37}}, {Key::Multiply, true}},
		{{1, {0x38}}, {Key::LAlt, true}},
		{{1, {0x39}}, {Key::Space, true}},
		{{1, {0x3A}}, {Key::CapsLock, true}},
		{{1, {0x3B}}, {Key::F1, true}},
		{{1, {0x3C}}, {Key::F2, true}},
		{{1, {0x3D}}, {Key::F3, true}},
		{{1, {0x3E}}, {Key::F4, true}},
		{{1, {0x3F}}, {Key::F5, true}},
		{{1, {0x40}}, {Key::F6, true}},
		{{1, {0x41}}, {Key::F7, true}},
		{{1, {0x42}}, {Key::F8, true}},
		{{1, {0x43}}, {Key::F9, true}},
		{{1, {0x44}}, {Key::F10, true}},
		{{1, {0x45}}, {Key::NumpadLock, true}},
		{{1, {0x46}}, {Key::ScrollLock, true}},
		{{1, {0x47}}, {Key::Numpad7, true}},
		{{1, {0x48}}, {Key::Numpad8, true}},
		{{1, {0x49}}, {Key::Numpad9, true}},
		{{1, {0x4A}}, {Key::Subtract, true}},
		{{1, {0x4B}}, {Key::Numpad4, true}},
		{{1, {0x4C}}, {Key::Numpad5, true}},
		{{1, {0x4D}}, {Key::Numpad6, true}},
		{{1, {0x4E}}, {Key::Add, true}},
		{{1, {0x4F}}, {Key::Numpad1, true}},
		{{1, {0x50}}, {Key::Numpad2, true}},
		{{1, {0x51}}, {Key::Numpad3, true}},
		{{1, {0x52}}, {Key::Numpad0, true}},
		{{1, {0x53}}, {Key::NumpadPeriod, true}},
		{{1, {0x57}}, {Key::F11, true}},
		{{1, {0x58}}, {Key::F12, true}},
		{{1, {0x81}}, {Key::Escape, false}},
		{{1, {0x82}}, {Key::Num1, false}},
		{{1, {0x83}}, {Key::Num2, false}},
		{{1, {0x84}}, {Key::Num3, false}},
		{{1, {0x85}}, {Key::Num4, false}},
		{{1, {0x86}}, {Key::Num5, false}},
		{{1, {0x87}}, {Key::Num6, false}},
		{{1, {0x88}}, {Key::Num7, false}},
		{{1, {0x89}}, {Key::Num8, false}},
		{{1, {0x8A}}, {Key::Num9, false}},
		{{1, {0x8B}}, {Key::Num0, false}},
		{{1, {0x8C}}, {Key::Dash, false}},
		{{1, {0x8D}}, {Key::Equal, false}},
		{{1, {0x8E}}, {Key::BackSpace, false}},
		{{1, {0x8F}}, {Key::Tab, false}},
		{{1, {0x90}}, {Key::Q, false}},
		{{1, {0x91}}, {Key::W, false}},
		{{1, {0x92}}, {Key::E, false}},
		{{1, {0x93}}, {Key::R, false}},
		{{1, {0x94}}, {Key::T, false}},
		{{1, {0x95}}, {Key::Y, false}},
		{{1, {0x96}}, {Key::U, false}},
		{{1, {0x97}}, {Key::I, false}},
		{{1, {0x98}}, {Key::O, false}},
		{{1, {0x99}}, {Key::P, false}},
		{{1, {0x9A}}, {Key::LBracket, false}},
		{{1, {0x9B}}, {Key::RBracket, false}},
		{{1, {0x9C}}, {Key::Return, false}},
		{{1, {0x9D}}, {Key::LControl, false}},
		{{1, {0x9E}}, {Key::A, false}},
		{{1, {0x9F}}, {Key::S, false}},
		{{1, {0xA0}}, {Key::D, false}},
		{{1, {0xA1}}, {Key::F, false}},
		{{1, {0xA2}}, {Key::G, false}},
		{{1, {0xA3}}, {Key::H, false}},
		{{1, {0xA4}}, {Key::J, false}},
		{{1, {0xA5}}, {Key::K, false}},
		{{1, {0xA6}}, {Key::L, false}},
		{{1, {0xA7}}, {Key::SemiColon, false}},
		{{1, {0xA8}}, {Key::Quote, false}},
		{{1, {0xA9}}, {Key::Tilde, false}},
		{{1, {0xAA}}, {Key::LShift, false}},
		{{1, {0xAB}}, {Key::BackSlash, false}},
		{{1, {0xAC}}, {Key::Z, false}},
		{{1, {0xAD}}, {Key::X, false}},
		{{1, {0xAE}}, {Key::C, false}},
		{{1, {0xAF}}, {Key::V, false}},
		{{1, {0xB0}}, {Key::B, false}},
		{{1, {0xB1}}, {Key::N, false}},
		{{1, {0xB2}}, {Key::M, false}},
		{{1, {0xB3}}, {Key::Comma, false}},
		{{1, {0xB4}}, {Key::Period, false}},
		{{1, {0xB5}}, {Key::Slash, false}},
		{{1, {0xB6}}, {Key::RShift, false}},
		{{1, {0xB7}}, {Key::Multiply, false}},
		{{1, {0xB8}}, {Key::LAlt, false}},
		{{1, {0xB9}}, {Key::Space, false}},
		{{1, {0xBA}}, {Key::CapsLock, false}},
		{{1, {0xBB}}, {Key::F1, false}},
		{{1, {0xBC}}, {Key::F2, false}},
		{{1, {0xBD}}, {Key::F3, false}},
		{{1, {0xBE}}, {Key::F4, false}},
		{{1, {0xBF}}, {Key::F5, false}},
		{{1, {0xC0}}, {Key::F6, false}},
		{{1, {0xC1}}, {Key::F7, false}},
		{{1, {0xC2}}, {Key::F8, false}},
		{{1, {0xC3}}, {Key::F9, false}},
		{{1, {0xC4}}, {Key::F10, false}},
		{{1, {0xC5}}, {Key::NumpadLock, false}},
		{{1, {0xC6}}, {Key::ScrollLock, false}},
		{{1, {0xC7}}, {Key::Numpad7, false}},
		{{1, {0xC8}}, {Key::Numpad8, false}},
		{{1, {0xC9}}, {Key::Numpad9, false}},
		{{1, {0xCA}}, {Key::Subtract, false}},
		{{1, {0xCB}}, {Key::Numpad4, false}},
		{{1, {0xCC}}, {Key::Numpad5, false}},
		{{1, {0xCD}}, {Key::Numpad6, false}},
		{{1, {0xCE}}, {Key::Add, false}},
		{{1, {0xCF}}, {Key::Numpad1, false}},
		{{1, {0xD0}}, {Key::Numpad2, false}},
		{{1, {0xD1}}, {Key::Numpad3, false}},
		{{1, {0xD2}}, {Key::Numpad0, false}},
		{{1, {0xD3}}, {Key::NumpadPeriod, false}},
		{{1, {0xD7}}, {Key::F11, false}},
		{{1, {0xD8}}, {Key::F12, false}},
		{{2, {0xE0, 0x1C}}, {Key::NumpadReturn, true}},
		{{2, {0xE0, 0x1D}}, {Key::RControl, true}},
		{{2, {0xE0, 0x35}}, {Key::Divide, true}},
		{{2, {0xE0, 0x38}}, {Key::RAlt, true}},
		{{2, {0xE0, 0x47}}, {Key::Home, true}},
		{{2, {0xE0, 0x48}}, {Key::Up, true}},
		{{2, {0xE0, 0x49}}, {Key::PageUp, true}},
		{{2, {0xE0, 0x4B}}, {Key::Left, true}},
		{{2, {0xE0, 0x4D}}, {Key::Right, true}},
		{{2, {0xE0, 0x4F}}, {Key::End, true}},
		{{2, {0xE0, 0x50}}, {Key::Down, true}},
		{{2, {0xE0, 0x51}}, {Key::PageDown, true}},
		{{2, {0xE0, 0x52}}, {Key::Insert, true}},
		{{2, {0xE0, 0x53}}, {Key::Delete, true}},
		{{2, {0xE0, 0x5B}}, {Key::LSystem, true}},
		{{2, {0xE0, 0x5C}}, {Key::RSystem, true}},
		{{2, {0xE0, 0x5D}}, {Key::Menu, true}},
		{{2, {0xE0, 0x9C}}, {Key::NumpadReturn, false}},
		{{2, {0xE0, 0x9D}}, {Key::RControl, false}},
		{{2, {0xE0, 0xB5}}, {Key::Divide, false}},
		{{2, {0xE0, 0xB8}}, {Key::RAlt, false}},
		{{2, {0xE0, 0xC7}}, {Key::Home, false}},
		{{2, {0xE0, 0xC8}}, {Key::Up, false}},
		{{2, {0xE0, 0xC9}}, {Key::PageUp, false}},
		{{2, {0xE0, 0xCB}}, {Key::Left, false}},
		{{2, {0xE0, 0xCD}}, {Key::Right, false}},
		{{2, {0xE0, 0xCF}}, {Key::End, false}},
		{{2, {0xE0, 0xD0}}, {Key::Down, false}},
		{{2, {0xE0, 0xD1}}, {Key::PageDown, false}},
		{{2, {0xE0, 0xD2}}, {Key::Insert, false}},
		{{2, {0xE0, 0xD3}}, {Key::Delete, false}},
		{{2, {0xE0, 0xDB}}, {Key::LSystem, false}},
		{{2, {0xE0, 0xDC}}, {Key::RSystem, false}},
		{{2, {0xE0, 0xDD}}, {Key::Menu, false}},
		{{4, {0xE0, 0x2A, 0xE0, 0x37}}, {Key::PrintScreen, true}},
		{{4, {0xE0, 0xB7, 0xE0, 0xAA}}, {Key::PrintScreen, false}},
		{{6, {0xE1, 0x1D, 0x45, 0xE1, 0x9D, 0xC5}}, {Key::Pause, true}}
	},
	{
	},
	{
	}
};

}// namespace ps2
