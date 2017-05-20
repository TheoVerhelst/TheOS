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

/// Gets the integer logarithm in base two of the given number, except for 0
/// where 0 is returned.
/// \param value The input value.
/// \tparam T Any unsigned integer type.
/// \tparam The logarithm in base two.
/// \return 0 if value == 0, log_2(value) otherwise.
template <typename T>
constexpr T log2(T value);

/// Gets the minimum betwee two values.
/// \param first The first value to compare.
/// \param second The second value to compare.
/// \tparam T Any comparable numerical type
/// \return first <= second ? first : second
template <typename T>
constexpr T min(T first, T second);

/// Gets the maximum betwee two values.
/// \param first The first value to compare.
/// \param second The second value to compare.
/// \tparam T Any comparable numerical type
/// \return first >= second ? first : second
template <typename T>
constexpr T max(T first, T second);

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
	constexpr T zero{static_cast<T>(0U)}, two{static_cast<T>(2U)};
	T res{zero};
	// Divide value by two value until it equals 0
	while((value /= two) > zero)
		++res;
	return res;
}

template <typename T>
constexpr T min(T first, T second)
{
	return first <= second ? first : second;
}

template <typename T>
constexpr T max(T first, T second)
{
	return first >= second ? first : second;
}

} // namespace math

#endif // MATH_HPP
