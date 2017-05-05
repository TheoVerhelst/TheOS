#ifndef MATH_HPP
#define MATH_HPP

namespace math
{

/// Gets the absolute value of the given number.
/// \param value A number.
/// \tparam T Any signed numerical type
/// \return n > 0 ? n : -n;
template <typename T>
constexpr T abs(T value);

/// Gets the integer logarithm in base two of the given number.
/// \param value The input value.
/// \tparam T Any unsigned integer type
/// \tparam The logarithm in base two.
template <typename T>
constexpr T log2(T value);

} // namespace math

namespace math
{

template <typename T>
constexpr T abs(T value)
{
	return value >= static_cast<T>(0) ? value : -value;
}

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

} // namespace math

#endif // MATH_HPP
