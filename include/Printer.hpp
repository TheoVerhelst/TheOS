#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <cstddef>
#include <cstdint>

class Printer
{
	public:
		Printer& setBase(int newBase);
		Printer& setShowPrefix(bool newShowPrefix);
		Printer& operator<<(char arg);
		Printer& operator<<(const char* arg);
		Printer& operator<<(short int arg);
		Printer& operator<<(short unsigned int arg);
		Printer& operator<<(int arg);
		Printer& operator<<(unsigned int arg);
		Printer& operator<<(long int arg);
		Printer& operator<<(long unsigned int arg);
		Printer& operator<<(bool arg);
		template <typename T>
		Printer& operator<<(const T* arg)
		{
			*this << reinterpret_cast<uintptr_t>(arg);
			return *this;
		}

	private:
		int _base = 10;
		bool _showPrefix = true;
		static const size_t _bufferLength = 32UL;
		static constexpr const char* _alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";
		static const char* _prefixes[];
};

extern Printer out;

#endif// PRINTER_HPP
