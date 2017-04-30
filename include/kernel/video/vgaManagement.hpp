#ifndef VGA_MANAGEMENT_H
#define VGA_MANAGEMENT_H

#include <std/cstdint>
#include <std/cstddef>

/// \addtogroup Kernel
/// \{

/// VGA hardware interface
namespace vga
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
		explicit operator uint8_t() const;

	private:
		uint8_t _foreground:4;
		uint8_t _background:4;
};
static_assert(sizeof(ColourProfile) == 1, "ColourProfile must be 8-bits");

class Entry
{
	public:
		Entry(char character, const ColourProfile& colourProfile);
		explicit operator uint16_t() const;

	private:
		uint8_t _character;
		uint8_t _colourProfile;
};
static_assert(sizeof(Entry) == 2, "Entry must be 16-bits");

const size_t width{80};
const size_t height{25};

/// defined location on the VGA buffer
Entry* const buffer{reinterpret_cast<Entry*>(0xC00B8000)};

constexpr inline size_t coordToIndex(size_t x, size_t y)
{
	return y * width + x;
}


}// namespace VGA

/// \}

#endif// VGA_MANAGEMENT_H
