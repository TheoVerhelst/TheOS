#include <kernel/video/vgaManagement.hpp>

namespace vga
{

ColourProfile::ColourProfile(Colour foreground, Colour background):
	_color{
			static_cast<uint8_t>(foreground)
			|
			(static_cast<uint8_t>(background) << 4)
	}
{
}

ColourProfile::operator uint8_t () const
{
	return static_cast<uint8_t>(_foreground) | (static_cast<uint8_t>(_background) << 4);
}

Entry::Entry(char character, const ColourProfile& colourProfile):
	_character{static_cast<uint8_t>(character)},
	_colourProfile{static_cast<uint8_t>(colourProfile)}
{
}

Entry::operator uint16_t() const
{
	return static_cast<uint16_t>(_character) | (static_cast<uint16_t>(_colourProfile) << 8);
}

} // namespace vga
