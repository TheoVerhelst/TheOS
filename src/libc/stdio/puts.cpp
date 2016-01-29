#include <stdio.hpp>
#include <kernel/terminal/Terminal.hpp>

int puts(const char * str)
{
	terminal.putString(str);
	putchar('\n');
	return 1;
}
