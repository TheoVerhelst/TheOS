#include <cpp/mem.hpp>
#include <kernel/io.hpp>
#include <kernel/vga/VgaTerminal.hpp>

const vga::ColourProfile VgaTerminal::_defaultColourProfile{vga::Colour::LightGrey, vga::Colour::Black};

VgaTerminal::VgaTerminal():
	_row{0},
	_column{0},
	_profile{vga::Colour::LightGrey, vga::Colour::Black},
	_emptyCell{' ', _profile},
	_writing{false}
{
	clearScreen();
}

void VgaTerminal::setColourProfile(vga::ColourProfile profile)
{
	_profile = profile;
	_emptyCell = vga::Entry(' ', _profile);
}

void VgaTerminal::putEntryAt(char c, vga::ColourProfile profile, size_t x, size_t y)
{
	vga::buffer[vga::coordToIndex(x, y)] = vga::Entry(c, profile);
}

void VgaTerminal::newLine(void)
{
	_column = 0;
	++_row;
	if(_row == vga::height)
		scrollUp();
}

void VgaTerminal::putChar(char c)
{
	if(c == '\n')
		newLine();
	else if(c == '\b')
		putEntryAt(' ', _profile, --_column, _row);
	else if(c == '\t')
		putString("        ");
	else if(c != '\0')
	{
		putEntryAt(c, _profile, _column++, _row);
		if(_column == vga::width)
			newLine();
	}
	if(!_writing)
		moveCursor(_column, _row);
}

void VgaTerminal::putString(const char* str)
{
	while(*str != '\0')
		putChar(*(str++));
}

void VgaTerminal::scrollUp()
{
	--_row;
	mem::copy(vga::buffer, &vga::buffer[vga::coordToIndex(0, 1)],
	       (vga::width * (vga::height - 1)) * sizeof(vga::Entry));
	mem::set(&vga::buffer[vga::coordToIndex(0, vga::height - 1)], static_cast<uint16_t>(_emptyCell), vga::width);
}

void VgaTerminal::clearScreen()
{
	mem::set(vga::buffer, static_cast<uint16_t>(_emptyCell), vga::height*vga::width);
}

void VgaTerminal::moveCursor(size_t x, size_t y)
{
	const uint16_t location{static_cast<uint16_t>(vga::coordToIndex(x, y))};

	// set VGA registers using IO ports
	outb(vga::addressPort, vga::cursorLocationLow);
	outb(vga::dataPort, static_cast<uint8_t>(location & 0xFF));
	outb(vga::addressPort, vga::cursorLocationHigh);
	outb(vga::dataPort, static_cast<uint8_t>((location >> 8) & 0xFF));
}
