#include <kernel/terminal/Terminal.hpp>
#include <string.hpp>
#include <io/out.hpp>

VGA_entry_t Terminal::emptyCell = make_VGA_entry(' ', make_colour(COLOUR_WHITE, COLOUR_BLACK));

Terminal::Terminal()
{
	row = column = 0;
	colour = make_colour(COLOUR_WHITE, COLOUR_BLACK);
	buffer = (VGA_entry_t *)(VGA_BUFFER_ADDRESS);
	writing = false;
	clearScreen();
}

void Terminal::setColour(colour_t colour)
{
	colour = colour;
	emptyCell = make_VGA_entry(' ', colour);
}

void Terminal::putEntryAt(char c, colour_t colour, size_t x, size_t y)
{
	buffer[VGA_COORD_TO_IDX(x, y)] = make_VGA_entry(c, colour);
}

void Terminal::newLine(void)
{
	column = 0;
	++row;
	if(row == VGA_HEIGHT)
		scrollUp();
}

void Terminal::putChar(char c)
{
	if(c == '\n')
		newLine();
	else
	{
		putEntryAt(c, colour, column, row);
		++column;
		if(column == VGA_WIDTH)
			newLine();
	}
	if(!writing)
		moveCursor(column, row);
}

void Terminal::putString(const char *str)
{
	while(*str != '\0')
		putChar(*(str++));
}

void Terminal::scrollUp(void)
{
	memcpy(buffer, &buffer[VGA_COORD_TO_IDX(0, 1)],
	       (VGA_WIDTH*(VGA_HEIGHT-1))*sizeof(VGA_entry_t));
	memsetw(&buffer[VGA_COORD_TO_IDX(0, VGA_HEIGHT-1)], emptyCell, VGA_WIDTH);
}

void Terminal::clearScreen(void)
{
	memsetw(buffer, emptyCell, VGA_HEIGHT*VGA_WIDTH);
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

