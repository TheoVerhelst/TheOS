#ifndef STRING_HPP
#define STRING_HPP

#include <std/cstddef>

/// Functions related to native C strings.
namespace string // TODO rename to str
{
	/// Returns the length of the given null-terminated byte string, that is, the
	/// number of characters in a character array whose first element is pointed to
	/// by str up to and not including the first null character.
	/// \param str Pointer to the null-terminated byte string to be analyzed.
	/// \return The length of the null-terminated byte string \a str.
	size_t length(const char* str);

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
	char* copy(char* dest, const char* src);
}



#endif // STRING_HPP
