#include <iostream>
#include <cpp/Printer.hpp>
#include <test/StandardTerminal.hpp>

StandardTerminal terminal;
Printer out{terminal};

void StandardTerminal::putChar(char c)
{
    std::cout << c;
}

void StandardTerminal::putString(const char* str)
{
    std::cout << str;
}
