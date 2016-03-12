#ifndef PRINTER_HPP
#define PRINTER_HPP

#include <cstddef>
#include <cstdint>

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
		enum Flags : unsigned int
		{
			/// Use an automatic base for displaying numbers (hexadecimal for
			/// pointers, and decimal for the rest). If this flag is set, then
			/// Hexadecimal, Decimal and Binary flags are ignored.
			AutoBase     = 1 << 0,

			/// Use the hexadecimal base for displaying numbers, the used prefix
			/// is 0x.
			Hexadecimal  = 1 << 1,

			/// Use the decimal base for displaying numbers, there is no prefix
			/// for this base.
			Decimal      = 1 << 2,

			/// Use the binary base for displaying numbers, the used prefix is
			/// 0b.
			Binary       = 1 << 3,

			/// If set, booleans are printed as "true" or "false" rather than
			/// "1" or "0".
			BoolAlpha    = 1 << 4,

			/// If this flag is set, then the prefix is shown only for pointers,
			/// and is hidden for other numbers. If set, ShowBase is ignored.
			AutoShowBase = 1 << 5,

			/// If set, the base prefix is always shown (unless AutoShowBase
			/// is set).
			ShowBase     = 1 << 6,

			/// If set, the "+" character is printed for each positive number,
			/// and the "-" character is printed for each negative number. If
			/// unset, only the "-" character is printed, if the number is
			/// negative.
			ShowPos      = 1 << 7,

			/// If set, show the letters in uppercase. If unset, show the
			/// letters in lowercase. The letters can be part of the prefix or
			/// can be part of the number (for the hexaecimal base).
			Uppercase    = 1 << 8
		};

		//TODO Write manipulators

		/// Print a character to the terminal.
		/// \param arg The character to print.
		/// \return *this.
		Printer& operator<<(char arg);

		/// Print a character string to the terminal.
		/// \param arg The character string to print.
		/// \return *this.
		Printer& operator<<(const char* arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(short int arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(short unsigned int arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(int arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(unsigned int arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long int arg);

		/// Print a number to the terminal.
		/// \param arg The number to print.
		/// \return *this.
		Printer& operator<<(long unsigned int arg);

		/// Print a boolean to the terminal.
		/// \param arg The boolean to print.
		/// \return *this.
		Printer& operator<<(bool arg);

		/// Print a pointer to the terminal.
		/// \param arg The pointer to print.
		/// \return *this.
		Printer& operator<<(void* arg);

		/// Modify some flags of the printer by using a manipulator. This is
		/// intended to be used like this:
		/// \code
		/// out << hexadecimal << 32; // Prints "B0"
		/// \endcode
		/// \param manipulator A function pointer taking a Printer as argument.
		/// \return *this.
		Printer& operator<<(void (*manipulator)(Printer&));

		/// Set some of the internal flags. Manipulators should be used instead
		/// of this methods.
		/// \param flags The flags to set.
		void setFlags(unsigned int flags);

		/// Reset some of the internal flags. Manipulators should be used
		/// instead of this methods.
		/// \param flags The flags to reset.
		void resetFlags(unsigned int flags);

	private:
		/// Get the corresponding uppsercase character if there is one, \a ch
		/// otherwhise. This differs from the standard std::to_upper because
		/// this only work for the 26 letters of the basic ASCII character set.
		/// \param ch The character to convert.
		/// \return ch + ('A' - 'a') if ch >= 'a' and ch <= 'z', ch otherwhise.
		static char toUpper(char ch);

		/// The flags used to parametrize the manner of how are printed
		/// variables. Inteded to be used with Flags.
		/// \see Flags
		unsigned int _flags{Flags::AutoBase | Flags::BoolAlpha | Flags::AutoShowBase | Flags::Uppercase};

		/// The length of the buffer internally to display numbers. This should
		/// be equal or greater than the maximum number of digit that a number
		/// can have it the smallest displayable base (binary).
		static constexpr size_t _bufferLength{32UL};

		/// The alphabet used for numbers.
		static constexpr const char* _alphabet = "0123456789abcdefghijklmnopqrstuvwxyz";

		/// All prefixes used for different bases. Most are empty because they
		/// never will be used.
		static constexpr const char* _prefixes[] = {"", "0b", "", "", "", "", "", "0", "",
			"", "", "", "", "", "", "0x", "", "", "", "", "", "", "", "", "", ""};
};

/// The main printer instance.
extern Printer out;

/// \}

#endif// PRINTER_HPP
