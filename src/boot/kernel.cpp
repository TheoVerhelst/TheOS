#if defined (__linux__) || !defined (__i386__)
 #error "Must be cross-compiled i686-elf to work properly!"
#endif

#include <stdio.hpp>
#include <kernel/terminal/terminal.hpp>

struct terminal_s terminal;

extern "C" void kernel_main()
{
	puts("This is BermudOS with puts!");
	printf("This is BermudOS with printf!");
}

