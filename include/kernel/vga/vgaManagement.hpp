#ifndef VGA_MANAGEMENT_H
#define VGA_MANAGEMENT_H

#include <std/cstdint>
#include <std/cstddef>

/// VGA hardware interface, assuming that we use text-mode VGA.
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
		// bits 0 -> 3: foreground color.
		/// bits 4 -> 7: background color.
		uint8_t _color;
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

/// defined location of the VGA memory buffer
Entry* const buffer{reinterpret_cast<Entry*>(0xB8000)};

/// IO port used to send the address of a VGA register to the VGA chip. When an
/// address is sent on this port and data is sent on the VGA data port, this
/// data is set into the VGA register.
constexpr uint16_t addressPort{0x3D4};

/// The port used to send data into the VGA registers.
constexpr uint16_t dataPort{0x3D5};

/// The address of the VGA register containing the low part (the bit 0-7) of the
/// location of the cursor on the screen.
constexpr uint8_t cursorLocationLow{0x0F};

/// The address of the VGA register containing the high part (the bit 8-15) of
/// the location of the cursor on the screen.
constexpr uint8_t cursorLocationHigh{0x0E};

constexpr inline size_t coordToIndex(size_t x, size_t y);

} // namespace vga

namespace vga
{

constexpr inline size_t coordToIndex(size_t x, size_t y)
{
	return y * width + x;
}

} // namespace vga

#endif // VGA_MANAGEMENT_H
