#ifndef STDIO_HPP
#define STDIO_HPP

#include <stdarg.h>

int printf(const char * , ...);
int vprintf(const char * , va_list);

int puts(const char * );

int putchar(int);

#endif// STDIO_HPP

