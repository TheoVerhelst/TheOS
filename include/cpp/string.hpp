#ifndef STRING_HPP
#define STRING_HPP

#include <std/cstddef>
#include <std/cstdint>

/// Functions related to native C strings.
namespace str
{
	/// Returns the length of the given null-terminated byte string, that is,
	/// the number of characters in a character array whose first element is
	/// pointed to by str up to and not including the last null character.
	/// \param str Pointer to the null-terminated byte string to be analyzed.
	/// \return The length of the null-terminated byte string \a str.
	size_t length(const char* str);

	/// Copies the null-terminated byte string pointed to by \a src, including
	/// the null terminator, to the character array whose first element is
	/// pointed to by \a dest.
	/// The behavior is undefined if the \a dest array is not large enough. The
	/// behavior is undefined if the strings overlap. The behavior is undefined
	/// if either \a dest is not a pointer to a character array or \a src is not
	/// a pointer to a null-terminated byte string.
	/// \param dest Pointer to the character array to write to.
	/// \param src pointer to the null-terminated byte string to copy from.
	/// \return Returns a copy of dest.
	char* copy(char* dest, const char* src);

	/// Appends at most count characters from the character array pointed to by
	/// src, stopping if the null character is found, to the end of the
	/// null-terminated byte string pointed to by dest. The character src[0]
	/// replaces the null terminator at the end of dest. The terminating null
	/// character is always appended in the end (so the maximum number of bytes
	/// the function may write is count+1).
	/// \param dest pointer to the null-terminated byte string to append to
	/// \param src pointer to the character array to copy from
	/// \param count maximum number of characters to copy
	/// \param a copy of dest
	char* concat(char* dest, const char* src, size_t n);

	template <typename T>
	char* numberToString(char* dest, size_t bufferLength, T arg,
			unsigned int numericBase = 10u, bool showBase = false);

} // namespace str

namespace str
{

template <typename T>
char* toString(char* dest, size_t bufferLength, T arg, unsigned int numericBase = 10, bool showBase = false)
{

	// The alphabet used for numbers.
	static constexpr const char* alphabet = "0123456789abcdef";

	// All prefixes used for different bases. Most are empty because they
	// never will be used.
	static constexpr const char* prefixes[] = {"", "0b", "", "", "", "",
		"", "0", "", "", "", "", "", "", "", "0x"};

	size_t i{0};
	const T zero{static_cast<T>(0)};

	// Insert the minus sign if needed
	if(arg < zero) {
		dest[i++] = '-';
		arg = -arg;
	}

	// Insert the characters of the base if needed
	if(showBase)
	{
		const char* baseString{prefixes[numericBase - 1]};
		copy(&dest[i], baseString);
		i += length(baseString);
	}

	// Insert the zero character if needed (won't be done otherwise)
	if(arg == zero)
		dest[i++] = '0';

	size_t firstDigit{i};

	while(arg > zero and i < bufferLength)
	{
		dest[i++] = alphabet[arg % numericBase];
		arg /= numericBase;
	}

	size_t lastDigit{i - 1};

	dest[i++] = '\0';

	// Reverse the string
	char tmp;
	while(firstDigit < lastDigit)
	{
		tmp = dest[lastDigit];
		dest[lastDigit] = dest[firstDigit];
		dest[firstDigit] = tmp;
		firstDigit++;
		lastDigit--;
	}

	return dest;
}

} // namespace str

#endif // STRING_HPP
