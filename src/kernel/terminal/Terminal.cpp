#include <kernel/terminal/Terminal.hpp>
#include <string.hpp>
#include <io/out.hpp>

Terminal::Terminal():
	_row{0},
	_column{0},
	_profile(VGA::Colour::LightGrey, VGA::Colour::Black),
	_emptyCell{' ', _profile},
	_writing{false}
{
	clearScreen();
}

void Terminal::setColourProfile(VGA::ColourProfile profile)
{
	_profile = profile;
	_emptyCell = VGA::Entry(' ', _profile);
}

void Terminal::putEntryAt(char c, VGA::ColourProfile profile, size_t x, size_t y)
{
	VGA::buffer[VGA::coordToIndex(x, y)] = VGA::Entry(c, profile);
}

void Terminal::newLine(void)
{
	_column = 0;
	++_row;
	if(_row == VGA::height)
		scrollUp();
}

void Terminal::putChar(char c)
{
	if(c == '\n')
		newLine();
	else
	{
		putEntryAt(c, _profile, _column, _row);
		++_column;
		if(_column == VGA::width)
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
	memcpy(VGA::buffer, &VGA::buffer[VGA::coordToIndex(0, 1)],
	       (VGA::width * (VGA::height - 1)) * sizeof(VGA::Entry));
	memsetw(&VGA::buffer[VGA::coordToIndex(0, VGA::height-1)], _emptyCell.getValue(), VGA::width);
}

void Terminal::clearScreen()
{
	memsetw(VGA::buffer, _emptyCell.getValue(), VGA::height*VGA::width);
}

void Terminal::moveCursor(int x, int y)
{
	uint16_t location = (y*VGA::width) + x;

	/* 0x3D4-0x3D5 are in VGA address space */
	outb(0x3D4, 0x0F);
	outb(0x3D5, (uint8_t)(location & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (uint8_t)((location>>8) & 0xFF));
}

