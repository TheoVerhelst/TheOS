#ifndef IN_HPP
#define IN_HPP

#include <cstdint>

/// Get a byte from the given I/O port.
/// \param port The port to listen to.
/// \return A byte coming from the port.
uint8_t inb(uint16_t port);

#endif// IN_HPP
