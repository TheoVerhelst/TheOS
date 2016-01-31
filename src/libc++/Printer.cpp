#include <Printer.hpp>
#include <string.hpp>
#include <kernel/terminal/Terminal.hpp>

Terminal terminal;

const char* Printer::_prefixes[] = {"", "0b", "", "", "", "", "", "0", "",
			"", "", "", "", "", "", "0x", "", "", "", "", "", "", "", "", "", ""};

Printer& Printer::setBase(int newBase)
{
	_base = newBase;
	return *this;
}
Printer& Printer::setShowPrefix(bool newShowPrefix)
{
	_showPrefix = newShowPrefix;
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

	if(_showPrefix)
	{
		strcpy(&buffer[index], _prefixes[_base - 1]);
		index += strlen(_prefixes[_base - 1]);
	}
	const int begin{index};

	if(arg == 0)
		buffer[index++] = '0';

	while(arg > 0)
	{
		const long int remainder{arg % _base};
		buffer[index++] = _alphabet[remainder];
		arg /= _base;
	}
	buffer[index--] = '\0';

	//Reverse digits
	int reverseIndex{begin};
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

	if(_showPrefix)
	{
		strcpy(&buffer[index], _prefixes[_base - 1]);
		index += strlen(_prefixes[_base - 1]);
	}
	const int begin{index};

	if(arg == 0)
		buffer[index++] = '0';

	while(arg > 0)
	{
		const long unsigned int remainder{arg % _base};
		buffer[index++] = _alphabet[remainder];
		arg /= _base;
	}
	buffer[index--] = '\0';

	//Reverse digits
	int reverseIndex{begin};
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

