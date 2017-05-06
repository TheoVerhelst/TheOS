#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <std/cstddef>
#include <std/cstdint>
#include <cpp/AbstractTerminal.hpp>

/// \addtogroup Cpp
/// \{

/// Class that prints various fundamental types to the kernel terminal.
/// This class behaves a bit like std::basic_ostream, and is is part of the
/// pseudo-implementation of the standard C++ library. This class has far less
/// methods that std::basic_ostream, the needed methods will be added when
/// needed.
class Printer
{
	public:
		/// Different options that can be activated on the Printer object, by
		/// using Printer::setFlag.
		enum class Flags
		{
			/// Use the hexadecimal base for displaying numbers, the used prefix
			/// is 0x.
			Hexadecimal,

			/// Use the decimal base for displaying numbers, there is no prefix
			/// for this base.
			Decimal,

			/// Use the binary base for displaying numbers, the used prefix is
			/// 0b.
			Binary,

			/// If set, booleans are printed as "true" or "false" rather than
			/// "1" or "0".
			BoolAlpha,

			/// If set, booleans are printed as "0" or "1" rather than "true" or
			/// "false".
			NoBoolAlpha,

			/// If set, the base prefix is shown.
			ShowBase,

			/// If set, the base prefix is hidden.
			NoShowBase,
		};

		/// Constructor.
		/// \param terminal The terminal that will be used for output.
		Printer(AbstractTerminal& terminal);

		/// Prints a character to the terminal.
		/// \param arg The character to print.
		/// \return *this.
		Printer& operator<<(char arg);

		/// Prints a character string to the terminal.
		/// \param arg The character string to print.
		/// \return *this.
		Printer& operator<<(const char* arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(short int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(short unsigned int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(unsigned int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long unsigned int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long long int arg);

		/// Prints a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long long unsigned int arg);

		/// Prints a boolean to the terminal.
		/// \param arg The boolean to print.
		/// \return *this.
		Printer& operator<<(bool arg);

		/// Prints a pointer to the terminal.
		/// \param arg The pointer to print.
		/// \return *this.
		Printer& operator<<(void* arg);

		/// Modifies some flags of the printer. This should be used like this:
		/// \code
		/// out << Printer::Flags::hexadecimal << 32; // Prints "B0"
		/// \endcode
		/// \param arg a Flags object.
		/// \return *this.
		Printer& operator<<(const Flags& arg);

	private:
		char* convertToString(unsigned long long int arg, bool showMinus);

		AbstractTerminal& _terminal;
		size_t _numericBase{10};
		bool _boolAlpha{true};
		bool _showBase{false};

		/// The length of the buffer used internally to display numbers. This
		/// should be equal or greater than the maximum number of digit that a
		/// number can have in the smallest displayable base (binary).
		static constexpr size_t _bufferLength{sizeof(uintmax_t) * 8};

		char _buffer[_bufferLength];

		/// The alphabet used for numbers.
		static constexpr const char* _alphabet = "0123456789abcdef";

		/// All prefixes used for different bases. Most are empty because they
		/// never will be used.
		static constexpr const char* _prefixes[] = {"", "0b", "", "", "", "",
			"", "0", "", "", "", "", "", "", "", "0x"};
};

/// The main printer instance. Must be instanciated by the environnement, by
/// giving the terminal to use.
extern Printer out;

/// \}

#endif// PRINTER_HPP
