#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <stddef.h>

class Printer
{
	public:
		Printer& setBase(int newBase);
		Printer& operator<<(char arg);
		Printer& operator<<(const char* arg);
		Printer& operator<<(short int arg);
		Printer& operator<<(short unsigned int arg);
		Printer& operator<<(int arg);
		Printer& operator<<(unsigned int arg);
		Printer& operator<<(long int arg);
		Printer& operator<<(long unsigned int arg);
		Printer& operator<<(bool arg);

	private:
		int _base = 10;
		static const size_t _bufferLength = 32UL;
};

extern Printer out;

#endif// PRINTER_HPP
