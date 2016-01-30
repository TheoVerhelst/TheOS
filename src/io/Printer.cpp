#include <io/Printer.hpp>
#include <kernel/terminal/Terminal.hpp>

Terminal terminal;

Printer& Printer::setBase(int newBase)
{
	_base = newBase;
	return *this;
}

Printer& Printer::operator<<(char arg)
{
	terminal.putChar(arg);
	return *this;
}

Printer& Printer::operator<<(const char* arg)
{
	terminal.putString(arg);
	return *this;
}

Printer& Printer::operator<<(short int arg)
{
	return *this << static_cast<long int>(arg);
}

Printer& Printer::operator<<(short unsigned int arg)
{
	return *this << static_cast<long unsigned int>(arg);
}

Printer& Printer::operator<<(int arg)
{
	return *this << static_cast<long int>(arg);
}

Printer& Printer::operator<<(unsigned int arg)
{
	return *this << static_cast<long unsigned int>(arg);
}

Printer& Printer::operator<<(long int arg)
{
	const bool negative{arg < 0};
	char buffer[_bufferLength];
	int index{0};
	if(negative)
	{
		buffer[index++] = '-';
		arg = -arg;
	}
	while(arg > 0)
	{
		const long int remainder{arg % _base};
		arg /= _base;
		buffer[index++] = '0' + static_cast<char>(remainder);
	}
	buffer[index] = '\0';

	//Reverse digits
	int reverseIndex{negative ? 1 : 0};
	char tmp;
	while(reverseIndex < index)
	{
		tmp = buffer[reverseIndex];
		buffer[reverseIndex++] = buffer[index];
		buffer[index--] = tmp;
	}
	terminal.putString(buffer);
	return *this;
}

Printer& Printer::operator<<(long unsigned int arg)
{
	char buffer[_bufferLength];
	int index{0};
	while(arg > 0)
	{
		const unsigned long int remainder{arg % 10};
		buffer[index++] = '0' + static_cast<char>(remainder);
		arg /= 10;
	}
	buffer[index--] = '\0';

	//Reverse digits
	int reverseIndex{0};
	char tmp;
	while(reverseIndex < index)
	{
		tmp = buffer[reverseIndex];
		buffer[reverseIndex] = buffer[index];
		buffer[index] = tmp;
		reverseIndex++;
		index--;
	}
	terminal.putString(buffer);
	return *this;
}

Printer& Printer::operator<<(bool arg)
{
	return *this << (arg ? "true" : "false");
}

