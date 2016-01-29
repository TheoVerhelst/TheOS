#include <stdio.hpp>
#include <kernel/terminal/terminal.hpp>

int putchar(int c)
{
	terminal_putchar(c);
	return c;
}
