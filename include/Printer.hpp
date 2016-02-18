#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <cstddef>
#include <cstdint>

class Printer
{
	public:
		enum Flags : unsigned int
		{
			AutoBase     = 1 << 0,
			Hexadecimal  = 1 << 1,
			Decimal      = 1 << 2,
			Binary       = 1 << 3,
			BoolAlpha    = 1 << 4,
			AutoShowBase = 1 << 5,
			ShowBase     = 1 << 6,
			ShowPos      = 1 << 7,
			Uppercase    = 1 << 8
		};

		Printer& operator<<(char arg);
		Printer& operator<<(const char* arg);
		Printer& operator<<(short int arg);
		Printer& operator<<(short unsigned int arg);
		Printer& operator<<(int arg);
		Printer& operator<<(unsigned int arg);
		Printer& operator<<(long int arg);
		Printer& operator<<(long unsigned int arg);
		Printer& operator<<(bool arg);
		Printer& operator<<(void (*manipulator)(Printer&));
		template <typename T>
		Printer& operator<<(const T* arg)
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
		void setFlags(unsigned int flags);
		void resetFlags(unsigned int flags);

	private:
		static char toUpper(char ch);
		unsigned int _flags{Flags::AutoBase | Flags::BoolAlpha | Flags::AutoShowBase | Flags::Uppercase};
		static constexpr size_t _bufferLength{32UL};
		static constexpr const char* _alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
		static constexpr const char* _prefixes[] = {"", "0b", "", "", "", "", "", "0", "",
			"", "", "", "", "", "", "0x", "", "", "", "", "", "", "", "", "", ""};
};

extern Printer out;

#endif// PRINTER_HPP
