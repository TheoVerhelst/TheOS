#ifndef MATH_HPP
#define MATH_HPP

#include <type_traits>

/// \defgroup C C
/// Pseudo-implementation of the standard C library.
/// \{

/// Get the absolute value of the given number.
/// \param n A number.
/// \return n > 0 ? n : -n;
int abs(int n);

/// Get the absolute value of the given number.
/// \param n A number.
/// \return n > 0L ? n : -n;
long int abs(long int n);

/// Get the absolute value of the given number.
/// \param n A number.
/// \return n > 0LL ? n : -n;
long long int abs(long long int n);

template <typename T>
constexpr T log2(T value);

/// \}



template <typename T>
constexpr T log2(T value)
{
	T res{static_cast<T>(0U)};
	constexpr T one{static_cast<T>(1U)}, zero{res};
	// Divide value by two value until it equals 0
	while((value <<= one) > zero)
		++res;
	return res;
}

#endif// MATH_HPP
