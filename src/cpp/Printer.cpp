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
	terminal.putString(convertToString(static_cast<long long unsigned int>(arg), arg < 0));
	return *this;
}

Printer& Printer::operator<<(long long unsigned int arg)
{
	terminal.putString(convertToString(arg, false));
	return *this;
}

Printer& Printer::operator<<(bool arg)
{
	if(_boolAlpha)
		return *this << (arg ? "true" : "false");
	else
		return *this << (arg ? "1" : "0");
}

Printer& Printer::operator<<(void* arg)
{
	const size_t oldBase{_numericBase};
	const bool oldBoolAlpha{_boolAlpha};
	const bool oldShowBase{_showBase};
	*this << Flags::Hexadecimal << Flags::ShowBase << reinterpret_cast<uintptr_t>(arg);
	_numericBase = oldBase;
	_boolAlpha = oldBoolAlpha;
	_showBase = oldShowBase;
	return *this;
}

Printer& Printer::operator<<(const Flags& arg)
{
	switch(arg)
	{
		case Flags::Binary:
			_numericBase = 2;
			break;

		case Flags::Decimal:
			_numericBase = 10;
			break;

		case Flags::Hexadecimal:
			_numericBase = 16;
			break;

		case Flags::BoolAlpha:
			_boolAlpha = true;
			break;

		case Flags::NoBoolAlpha:
			_boolAlpha = false;
			break;

		case Flags::ShowBase:
			_showBase = true;
			break;

		case Flags::NoShowBase:
			_showBase = false;
			break;
	}
	return *this;
}

char* Printer::convertToString(unsigned long long int arg, bool showMinus)
{
	int index{0};

	if(showMinus)
		_buffer[index++] = '-';

	if(_showBase)
	{
		string::copy(&_buffer[index], _prefixes[_numericBase - 1]);
		index += string::length(_prefixes[_numericBase - 1]);
	}

	const int begin{index};

	if(arg == 0)
		_buffer[index++] = '0';

	while(arg > 0)
	{
		_buffer[index++] = _alphabet[arg % _numericBase];
		arg /= _numericBase;
	}
	_buffer[index--] = '\0';

	//Reverse digits
	int reverseIndex{begin};
	char tmp;
	while(reverseIndex < index)
	{
		tmp = _buffer[reverseIndex];
		_buffer[reverseIndex++] = _buffer[index];
		_buffer[index--] = tmp;
	}
	return _buffer;
}
