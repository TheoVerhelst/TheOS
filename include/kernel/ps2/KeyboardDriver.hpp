#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#include <cstddef>
#include <List.hpp>
#include <kernel/ps2/Driver.hpp>
#include <kernel/ps2/KeyboardMapper.hpp>

namespace ps2
{

class KeyboardDriver : public Driver
{
	public:
		void pollKeyboard();
		bool pendingEvent();// TODO find a better name
		KeyEvent getEvent();

	private:

		enum Command : uint8_t
		{
			SetLed                = 0xED,
			Echo                  = 0xEE,
			GetSetScanCode        = 0xF0,
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

		ScancodeSequence _currentSequence;
		List<KeyEvent> _eventQueue;
		KeyboardMapper _mapper{KeyboardMapper::Mapping::ScancodeSet1};
};

extern KeyboardDriver keyboardDriver;

}// namespace ps2

#endif// KEYBOARD_HPP
