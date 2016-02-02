#ifndef UTILITY_HPP
#define UTILITY_HPP

template<class T>
struct removeReference
{
	typedef T type;
};

template<class T>
struct removeReference<T&>
{
	typedef T type;
};

template<class T>
struct removeReference<T&&>
{
	typedef T type;
};

template <class T>
constexpr T&& forward(typename removeReference<T>::type& t)
{
	return static_cast<T&&>(t);
}

template <class T>
constexpr T&& forward(typename removeReference<T>::type&& t)
{
	return static_cast<T&&>(t);
}

#endif// UTILITY_HPP
