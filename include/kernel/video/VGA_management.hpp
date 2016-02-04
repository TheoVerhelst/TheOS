#ifndef VGA_MANAGEMENT_H
#define VGA_MANAGEMENT_H

#include <cstdint>
#include <cstddef>

// VGA hardware interface
namespace VGA
{

enum class Colour : uint8_t
{
	Black = 0,
	Blue,
	Green,
	Cyan,
	Red,
	Magenta,
	Brown,
	LightGrey,
	DarkGrey,
	LightBlue,
	LightGreen,
	LightCyen,
	LightRed,
	LightMagenta,
	LightBrown,
	White = 15
};

class ColourProfile
{
	public:
		ColourProfile(Colour foreground, Colour background);
		uint8_t getValue() const;

	private:
		uint8_t _value;
};

class Entry
{
	public:
		Entry(char c, const ColourProfile& profile);
		uint16_t getValue() const;

	private:
		uint16_t _value;
};

const size_t width{80};
const size_t height{25};
Entry * const buffer{reinterpret_cast<Entry*>(0xB8000)};// defined location on the VGA buffer

constexpr inline size_t coordToIndex(size_t x, size_t y)
{
	return y * width + x;
}


}// namespace VGA

#endif// VGA_MANAGEMENT_H
