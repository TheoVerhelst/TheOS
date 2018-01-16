#include <cpp/Printer.hpp>
#include <cpp/string.hpp>

constexpr size_t Printer::_bufferLength;

Printer::Printer(AbstractTerminal& terminal):
	_terminal{terminal}
{
}

Printer& Printer::operator<<(char arg)
{
	_terminal.putChar(arg);
	return *this;
}

Printer& Printer::operator<<(const char* arg)
{
	_terminal.putString(arg);
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
	_terminal.putString(str::toString(_buffer, _bufferLength, arg, _numericBase, _showBase));
	return *this;
}

Printer& Printer::operator<<(long long unsigned int arg)
{
	_terminal.putString(str::toString(_buffer, _bufferLength, arg, _numericBase, _showBase));
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
	*this << Flags::Hex << Flags::ShowBase << reinterpret_cast<uintptr_t>(arg);
	_numericBase = oldBase;
	_boolAlpha = oldBoolAlpha;
	_showBase = oldShowBase;
	return *this;
}

Printer& Printer::operator<<(const Flags& arg)
{
	switch(arg)
	{
		case Flags::Bin:
			_numericBase = 2;
			break;

		case Flags::Dec:
			_numericBase = 10;
			break;

		case Flags::Hex:
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
