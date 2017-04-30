#ifndef UTILITY_HPP
#define UTILITY_HPP

#include <std/type_traits>

/// Forwards an lvalue.
/// This function is used to implement "perfect forwarding".
/// \return The parameter cast to the specified type.
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type& t) noexcept
{
	return static_cast<T&&>(t);
}

/// Forwards an rvalue.
/// This function is used to implement "perfect forwarding".
/// \return The parameter cast to the specified type.
template<typename T>
constexpr T&& forward(typename std::remove_reference<T>::type&& t) noexcept
{
  static_assert(not std::is_lvalue_reference<T>::value, "template argument"
		" substituting T is an lvalue reference type");
  return static_cast<T&&>(t);
}

/// Converts a value to an rvalue.
/// \param t A thing of arbitrary type.
/// \return The parameter cast to an rvalue-reference to allow moving it.
template<typename T>
constexpr typename std::remove_reference<T>::type&& move(T&& t) noexcept
{
	return static_cast<typename std::remove_reference<T>::type&&>(t);
}

/// Swaps two values.
/// \param a A thing of arbitrary type.
/// \param b Another thing of arbitrary type.
template<typename T>
inline void swap(T& a, T& b)
noexcept(std::__and_<std::is_nothrow_move_constructible<T>, std::is_nothrow_move_assignable<T>>::value)
{
	T tmp = move(a);
	a = move(b);
	b = move(tmp);
}

#endif // UTILITY_HPP
