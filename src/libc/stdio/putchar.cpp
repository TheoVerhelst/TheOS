#include <stdio.hpp>
#include <kernel/terminal/Terminal.hpp>

int putchar(int c)
{
	terminal.putChar(c);
	return c;
}
