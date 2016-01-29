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
		void newLine();
		void scrollUp();
		void clearScreen();
		void putEntryAt(char, colour_t, size_t, size_t);
		void moveCursor(int, int);

		size_t _row;         /// Y coordinate
		size_t _column;      /// X coordinate
		colour_t _colour;    /// Colour of the cell
		VGA_entry_t _emptyCell;
		VGA_entry_t* _buffer;/// address of the buffer to write the data in
		bool _writing;

};

extern Terminal terminal;

#endif// TERMINAL_HPP
