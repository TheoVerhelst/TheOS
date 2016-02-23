#include <kernel/terminal/Terminal.hpp>
#include <string.hpp>
#include <io/out.hpp>

Terminal::Terminal():
	_row{0},
	_column{0},
	_profile(vga::Colour::LightGrey, vga::Colour::Black),
	_emptyCell{' ', _profile},
	_writing{false}
{
	clearScreen();
}

void Terminal::setColourProfile(vga::ColourProfile profile)
{
	_profile = profile;
	_emptyCell = vga::Entry(' ', _profile);
}

void Terminal::putEntryAt(char c, vga::ColourProfile profile, size_t x, size_t y)
{
	vga::buffer[vga::coordToIndex(x, y)] = vga::Entry(c, profile);
}

void Terminal::newLine(void)
{
	_column = 0;
	++_row;
	if(_row == vga::height)
		scrollUp();
}

void Terminal::putChar(char c)
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

void Terminal::putString(const char *str)
{
	while(*str != '\0')
		putChar(*(str++));
}

void Terminal::scrollUp()
{
	--_row;
	memcpy(vga::buffer, &vga::buffer[vga::coordToIndex(0, 1)],
	       (vga::width * (vga::height - 1)) * sizeof(vga::Entry));
	_memset(&vga::buffer[vga::coordToIndex(0, vga::height - 1)], static_cast<uint16_t>(_emptyCell), vga::width);
}

void Terminal::clearScreen()
{
	_memset(vga::buffer, static_cast<uint16_t>(_emptyCell), vga::height*vga::width);
}

void Terminal::moveCursor(int x, int y)
{
	uint16_t location = (y * vga::width) + x;

	/* 0x3D4-0x3D5 are in VGA address space */
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(location & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((location>>8) & 0xFF));
}

