#ifndef BYTE_HPP
#define BYTE_HPP

#include <std/cstddef>

/// This typedef is used to have a representation of a low-level byte, and is
/// intented to replace the usual void* for a typeless address. This tweak is
/// useful in memory managers.
typedef unsigned char Byte;

/// The number of bits in an address. The multiplication by eight is because
/// we "assume" that there is 8 bits in a byte.
// TODO rename, as it stands it implies a size in bytes, not in bits
constexpr size_t addressSize{sizeof(void*) * 8};

#endif // BYTE_HPP
