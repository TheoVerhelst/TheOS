#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <stddef.h>
#include <kernel/video/VGA_management.hpp>

/// Class managing the main terminal.
class Terminal
{
	public:
		Terminal();
		void setColour(colour_t);
		void putChar(char);
		void putString(const char *);

	private:
		void putEntryAt(char, colour_t, size_t, size_t);
		void newLine();
		void scrollUp();
		void clearScreen();
		void moveCursor(int, int);

		size_t row;         /// Y coordinate
		size_t column;      /// X coordinate
		colour_t colour;    /// Colour of the cell
		VGA_entry_t* buffer;/// address of the buffer to write the data in
		static VGA_entry_t emptyCell;
		bool writing;

};

extern Terminal terminal;

#endif// TERMINAL_HPP
