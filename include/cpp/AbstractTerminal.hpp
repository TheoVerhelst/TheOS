#ifndef ABSTRACTTERMINAL_HPP
#define ABSTRACTTERMINAL_HPP

/// \addtogroup Cpp
/// \{

/// Interface of a terminal, used to differenciate the kernel terminal from the
/// standard one (in unit test for the latter).
class AbstractTerminal
{
    public:
        /// Puts a character to the terminal.
        /// \param c The character to put.
    	virtual void putChar(char c) = 0;

        /// Puts a string to the terminal.
        /// \param str The string to put.
    	virtual void putString(const char* str) = 0;
};

/// \}

#endif// ABSTRACTTERMINAL_HPP
