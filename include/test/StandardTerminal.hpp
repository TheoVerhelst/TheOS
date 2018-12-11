#ifndef STANDARDTERMINAL_HPP
#define STANDARDTERMINAL_HPP

#include <cpp/AbstractTerminal.hpp>

/// Terminal implementation using std::cout, used to test classes using Printer.
class StandardTerminal : public AbstractTerminal
{
    public:
        /// Puts a character to the terminal.
        /// \param c The character to put.
    	virtual void putChar(char c) override;

        /// Puts a string to the terminal.
        /// \param str The string to put.
    	virtual void putString(const char* str) override;
};

#endif // STANDARDTERMINAL_HPP
