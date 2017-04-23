#include <Printer.hpp>
#include <string.hpp>
#include <kernel/terminal/Terminal.hpp>

Printer out;

constexpr size_t Printer::_bufferLength;
constexpr const char* Printer::_alphabet;
constexpr const char* Printer::_prefixes[];

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
	return *this << static_cast<long long int>(arg);
}

Printer& Printer::operator<<(short unsigned int arg)
{
	return *this << static_cast<long long unsigned int>(arg);
}

Printer& Printer::operator<<(int arg)
{
	return *this << static_cast<long long int>(arg);
}

Printer& Printer::operator<<(unsigned int arg)
{
	return *this << static_cast<long long unsigned int>(arg);
}

Printer& Printer::operator<<(long int arg)
{
	return *this << static_cast<long long int>(arg);
}

Printer& Printer::operator<<(long unsigned int arg)
{
	return *this << static_cast<long long unsigned int>(arg);
}
Printer& Printer::operator<<(long long int arg)
{
	const bool negative{arg < 0};
	char buffer[_bufferLength];
	int index{0};
	size_t base;
	if(_flags & Flags::AutoBase)
		base = 10;
	else if(_flags & Flags::Hexadecimal)
		base = 16;
	else if(_flags & Flags::Binary)
		base = 2;

	if(negative)
	{
		buffer[index++] = '-';
		arg = -arg;
	}
	else if(_flags & Flags::ShowPos)
	{
		buffer[index++] = '+';
		arg = -arg;
	}

	if(not (_flags & Flags::AutoShowBase) and  (_flags & Flags::ShowBase))
	{
		string::copy(&buffer[index], _prefixes[base - 1]);
		index += string::length(_prefixes[base - 1]);
	}

	const int begin{index};

	if(arg == 0)
		buffer[index++] = '0';

	while(arg > 0)
	{
		buffer[index++] = _alphabet[arg % base];
		arg /= base;
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

Printer& Printer::operator<<(long long unsigned int arg)
{
	char buffer[_bufferLength];
	int index{0};
	size_t base;
	if(_flags & Flags::AutoBase)
		base = 10;
	else if(_flags & Flags::Hexadecimal)
		base = 16;
	else if(_flags & Flags::Binary)
		base = 2;

	if(_flags & Flags::ShowPos)
	{
		buffer[index++] = '+';
		arg = -arg;
	}

	if(not (_flags & Flags::AutoShowBase) and  (_flags & Flags::ShowBase))
	{
		string::copy(&buffer[index], _prefixes[base - 1]);
		index += string::length(_prefixes[base - 1]);
	}

	const int begin{index};

	if(arg == 0)
		buffer[index++] = '0';

	while(arg > 0)
	{
		const auto remainder{arg % base};
		if(_flags & Flags::Uppercase)
			buffer[index++] = toUpper(_alphabet[remainder]);
		else
			buffer[index++] = _alphabet[remainder];
		arg /= base;
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
	if(_flags & Flags::BoolAlpha)
		return *this << (arg ? "true" : "false");
	else
		return *this << (arg ? "1" : "0");
}

Printer& Printer::operator<<(void* arg)
{
	const unsigned int oldFlags{_flags};
	if(_flags & Flags::AutoBase)
	{
		setFlags(Flags::Hexadecimal);
		resetFlags(Flags::AutoBase);
	}
	if(_flags & Flags::AutoShowBase)
	{
		setFlags(Flags::ShowBase);
		resetFlags(Flags::AutoShowBase);
	}
	*this << reinterpret_cast<uintptr_t>(arg);
	_flags = oldFlags;
	return *this;
}

void Printer::setFlags(unsigned int flags)
{
	_flags |= flags;
}

void Printer::resetFlags(unsigned int flags)
{
	_flags &= ~flags;
}

char Printer::toUpper(char ch)
{
	if(ch >= 'a' and ch <= 'z')
		return ch + ('A' - 'a');
	else
		return ch;
}
