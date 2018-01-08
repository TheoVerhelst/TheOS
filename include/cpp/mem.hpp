#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <std/cstddef>
#include <std/cstdint>

namespace mem
{

/// Copies count characters from the object pointed to by \a src to the object
/// pointed to by \a dest. Both objects are interpreted as arrays of unsigned
/// char.
///
/// The behavior is undefined if access occurs beyond the end of the \a dest
/// array. If the objects overlap, the behavior is undefined. The behavior is
/// undefined if either \a dest or \a src is a null pointer.
/// \param dest Pointer to the object to copy to.
/// \param src Pointer to the object to copy from.
/// \param count Number of bytes to copy.
void copy(void* dest, const void* src, size_t count);

/// Copies the value \a value into the memory place pointed to by \a dest.
///
/// \param dest Pointer to the object to copy.
/// \param value The value to fill.
/// \param count Number of times to fill.
void set(void* dest, uint16_t value, size_t count);

} // namespace mem

/// Copies the value \a value into the memory place pointed to by \a dest.
/// This function is needed as an extern "C" function by GCC since we are in
/// freestanding environment.
/// \param dest Pointer to the object to copy.
/// \param value The value to fill.
/// \param count Number of times to fill.
extern "C" void memset(void* dest, char value, size_t count);

#endif // MEMORY_HPP
