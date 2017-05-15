#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <std/cstdint>
#include <std/cstddef>
#include <cpp/Printer.hpp>
#include <kernel/ps2/Driver.hpp>
#include <kernel/ps2/ScancodeMapper.hpp>
#include <kernel/ps2/KeyEventMapper.hpp>

namespace ps2
{

class KeyboardDriver : public Driver
{
	public:
		void pollKeyboard();
		bool pendingCharacter();// TODO find a better name
		char getCharacter();

	private:

		enum Command : uint8_t
		{
			SetLed                = 0xED,
			Echo                  = 0xEE,
			GetSetScanCodeSet     = 0xF0,
			IdentifyKeyboard      = 0xF2,
			SetTypematic          = 0xF3,
			Enable                = 0xF4,
			Disable               = 0xF5,
			SetDefaultsParam      = 0xF6,
			AllRepeat             = 0xF7,
			AllPressRelease       = 0xF8,
			AllPressOnly          = 0xF9,
			AllRepeatPressRelease = 0xFA,
			SpecificRepeat        = 0xFB,
			SpecificPressRelease  = 0xFC,
			SpecificPressOnly     = 0xFD,
			Resend                = 0xFE,
			ResetAndSelfTest      = 0xFF,
		};

		Scancode _currentScancode;
		ScancodeMapper _scancodeMapper{ScancodeMapper::Mapping::ScancodeSet1};
		KeyEventMapper _keyEventMapper{KeyEventMapper::Mapping::AzertyFr};
};

} // namespace ps2



#endif // KEYBOARD_HPP
