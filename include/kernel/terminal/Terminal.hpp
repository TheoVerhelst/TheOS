#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <cstddef>
#include <kernel/video/vgaManagement.hpp>

/// Class managing the main terminal.
class Terminal
{
	public:
		Terminal();
		void setColourProfile(vga::ColourProfile profile);
		void putChar(char c);
		void putString(const char * str);

	private:
		void newLine();
		void scrollUp();
		void clearScreen();
		void putEntryAt(char c, vga::ColourProfile profile, size_t x, size_t y);
		void moveCursor(int x, int y);

		size_t _row;               /// Y coordinate
		size_t _column;            /// X coordinate
		vga::ColourProfile _profile;/// Colour of the cell
		vga::Entry _emptyCell;
		bool _writing;

};

#endif// TERMINAL_HPP
