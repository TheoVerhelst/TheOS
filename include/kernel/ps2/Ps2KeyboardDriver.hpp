#ifndef KEYBOARD_HPP
#define KEYBOARD_HPP

#include <cstdint>
#include <cstddef>
#include <kernel/ps2/Ps2Driver.hpp>

namespace ps2
{

class Ps2KeyboardDriver : public Ps2Driver
{
	public:
		void pollKeyboard();
		bool isBufferEmpty();
		void flushBuffer();

	private:
		static constexpr size_t _bufferSize{16};
		uint8_t _scanCodeBuffer[_bufferSize];
		size_t _bufferEnd{0};

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
};

extern Ps2KeyboardDriver keyboardDriver;

}// namespace ps2

#endif// KEYBOARD_HPP
