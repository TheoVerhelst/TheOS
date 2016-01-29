#include <kernel/terminal/Terminal.hpp>
#include <string.hpp>
#include <io/out.hpp>

Terminal::Terminal():
	_row{0},
	_column{0},
	_colour(make_colour(COLOUR_LIGHT_GREY, COLOUR_BLACK)),
	_emptyCell{make_VGA_entry(' ', _colour)},
	_buffer{(VGA_entry_t *)(VGA_BUFFER_ADDRESS)},
	_writing{false}
{
	clearScreen();
}

void Terminal::setColour(colour_t colour)
{
	_colour = colour;
	_emptyCell = make_VGA_entry(' ', _colour);
}

void Terminal::putEntryAt(char c, colour_t colour, size_t x, size_t y)
{
	_buffer[VGA_COORD_TO_IDX(x, y)] = make_VGA_entry(c, colour);
}

void Terminal::newLine(void)
{
	_column = 0;
	++_row;
	if(_row == VGA_HEIGHT)
		scrollUp();
}

void Terminal::putChar(char c)
{
	if(c == '\n')
		newLine();
	else
	{
		putEntryAt(c, _colour, _column, _row);
		++_column;
		if(_column == VGA_WIDTH)
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

void Terminal::scrollUp(void)
{
	memcpy(_buffer, &_buffer[VGA_COORD_TO_IDX(0, 1)],
	       (VGA_WIDTH*(VGA_HEIGHT-1))*sizeof(VGA_entry_t));
	memsetw(&_buffer[VGA_COORD_TO_IDX(0, VGA_HEIGHT-1)], _emptyCell, VGA_WIDTH);
}

void Terminal::clearScreen(void)
{
	memsetw(_buffer, _emptyCell, VGA_HEIGHT*VGA_WIDTH);
}

void Terminal::moveCursor(int x, int y)
{
	uint16_t location = (y*VGA_WIDTH) + x;

	/* 0x3D4-0x3D5 are in VGA address space */
	outb(0x3D4, 0x0F);
	outb(0x3D5, (BYTE)(location & 0xFF));
	outb(0x3D4, 0x0E);
	outb(0x3D5, (BYTE)((location>>8) & 0xFF));
}

