#ifndef IN_HPP
#define IN_HPP

#include <std/cstdint>

/// \defgroup Io I/O
/// Functions related to low level I/O and ports.
/// \{

/// Get a byte from the given I/O port.
/// \param port The port to listen to.
/// \return A byte coming from the port.
uint8_t inb(uint16_t port);

/// Write a byte to the given I/O port.
/// \param port The port to write to.
/// \param value To value to write.
void outb(uint16_t port, uint8_t value);

/// Wait for I/O.
void ioWait();

/// \}

#endif// IN_HPP
