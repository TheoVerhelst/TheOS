#ifndef UTILS_HPP
#define UTILS_HPP

template <typename UnsignedType>
bool test(UnsignedType value, size_t index)
{
	return value & (static_cast<size_t>(1) << index);
}

#endif// UTILS_HPP
