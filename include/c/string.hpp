#ifndef STRING_HPP
#define STRING_HPP

#include <stddef.h>
#include <stdint.h>

/// \addtogroup C
/// \{

extern "C"
{

/// Finds the first occurrence of \a ch (after conversion to char as if by
/// (char)ch) in the null-terminated byte string pointed to by \a str (each
/// character interpreted as unsigned char). The terminating null character is
/// considered to be a part of the string and can be found when searching for
/// '\0'.
///
/// The behavior is undefined if \a str is not a pointer to a null-terminated
/// byte string.
/// \param str Pointer to the null-terminated byte string to be analyzed.
/// \param ch Character to search for.
/// \return Pointer to the found character in str, or null pointer if no such
/// character is found.
char* strrchr(const char* str, int ch);

/// Returns the length of the given null-terminated byte string, that is, the
/// number of characters in a character array whose first element is pointed to
/// by str up to and not including the first null character.
/// \param str Pointer to the null-terminated byte string to be analyzed.
/// \return The length of the null-terminated byte string \a str.
size_t strlen(const char* str);

/// Copies the null-terminated byte string pointed to by \a src, including the
/// null terminator, to the character array whose first element is pointed to by
/// \a dest.
/// The behavior is undefined if the \a dest array is not large enough. The
/// behavior is undefined if the strings overlap. The behavior is undefined if
/// either \a dest is not a pointer to a character array or \a src is not a
/// pointer to a null-terminated byte string.
/// \param dest Pointer to the character array to write to.
/// \param src pointer to the null-terminated byte string to copy from.
/// \return Returns a copy of dest.
char* strcpy(char* dest, const char* src);

/// Copies the value \a ch (after conversion to unsigned char as if by
/// (unsigned char)ch) into each of the first \a count characters of the object
/// pointed to by \a dest.
///
/// The behavior is undefined if access occurs beyond the end of the \a dest
/// array. The behavior is undefined if \a dest is a null pointer.
/// \param dest Pointer to the object to fill.
/// \param ch Fill byte.
/// \param count Number of bytes to fill.
void* memset(void* dest, int ch, size_t count);

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
/// \return Returns a copy of dest.
void* memcpy(void* dest, const void* src, size_t count);

}// extern "C"

/// Overloaded of memset.
/// \see memset
/// \param dest Pointer to the object to fill.
/// \param ch Fill byte.
/// \param count Number of bytes to fill.
void* _memset(void* dest, uint8_t ch, size_t count);

/// Overloaded of memset.
/// \see memset
/// \param dest Pointer to the object to fill.
/// \param ch Fill byte.
/// \param count Number of bytes to fill.
void* _memset(void* dest, uint16_t ch, size_t count);

/// Overloaded of memset.
/// \see memset
/// \param dest Pointer to the object to fill.
/// \param ch Fill byte.
/// \param count Number of bytes to fill.
void* _memset(void* dest, uint32_t ch, size_t count);

/// \}

#endif// STRING_HPP
