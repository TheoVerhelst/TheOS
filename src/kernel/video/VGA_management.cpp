#include <kernel/video/VGA_management.hpp>

namespace VGA
{

ColourProfile::ColourProfile(Colour foreground, Colour background)
{
	_value = static_cast<uint8_t>(foreground) | (static_cast<uint8_t>(background) << 4);
}

uint8_t ColourProfile::getValue() const
{
	return _value;
}

Entry::Entry(char c, const ColourProfile& colour)
{
	_value = (uint16_t)(c) | (colour.getValue() << 8);
}

uint16_t Entry::getValue() const
{
	return _value;
}

}// namespace VGA
