#ifndef TERMINAL_HPP
#define TERMINAL_HPP

#include <std/cstddef>
#include <cpp/AbstractTerminal.hpp>
#include <kernel/vga/vgaManagement.hpp>

/// Class managing the kernel terminal.
class VgaTerminal : public AbstractTerminal
{
	public:
		/// Constructor.
		VgaTerminal();

		/// Changes the colours of the terminal.
		void setColourProfile(vga::ColourProfile profile);

        /// Puts a character to the terminal.
        /// \param c The character to put.
		virtual void putChar(char c) override;

        /// Puts a string to the terminal.
        /// \param str The string to put.
		virtual void putString(const char* str) override;

		static const vga::ColourProfile _defaultColourProfile;

	private:
		void newLine();
		void scrollUp();
		void clearScreen();
		void putEntryAt(char c, vga::ColourProfile profile, size_t x, size_t y);
		void moveCursor(int x, int y);

		size_t _row;                /// Y coordinate
		size_t _column;             /// X coordinate
		vga::ColourProfile _profile;/// Colour of the cell
		vga::Entry _emptyCell;
		bool _writing;
};

#endif // TERMINAL_HPP
