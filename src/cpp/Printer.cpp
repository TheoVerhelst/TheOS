#include <cpp/Printer.hpp>
#include <cpp/string.hpp>

constexpr size_t Printer::_bufferLength;
constexpr const char* Printer::_alphabet;
constexpr const char* Printer::_prefixes[];

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
	_terminal.putString(convertToString(static_cast<long long unsigned int>(arg), arg < 0));
	return *this;
}

Printer& Printer::operator<<(long long unsigned int arg)
{
	_terminal.putString(convertToString(arg, false));
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
	size_t i{0};

	if(showMinus)
		_buffer[i++] = '-';

	if(_showBase)
	{
		const char* baseString{_prefixes[_numericBase - 1]};
		string::copy(&_buffer[i], baseString);
		i += string::length(baseString);
	}

	if(arg == 0)
		_buffer[i++] = '0';

	size_t firstDigit{i};

	while(arg > 0 and i < _bufferLength)
	{
		_buffer[i++] = _alphabet[arg % _numericBase];
		arg /= _numericBase;
	}

	size_t lastDigit{i - 1};

	_buffer[i++] = '\0';

	// Reverse the string
	char tmp;
	while(firstDigit < lastDigit)
	{
		tmp = _buffer[lastDigit];
		_buffer[lastDigit] = _buffer[firstDigit];
		_buffer[firstDigit] = tmp;
		firstDigit++;
		lastDigit--;
	}

	return _buffer;
}
