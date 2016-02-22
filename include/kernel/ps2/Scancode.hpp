#ifndef SCANCODE_HPP
#define SCANCODE_HPP

#include <cstddef>
#include <cstdint>

namespace ps2
{

struct Scancode
{
	static constexpr size_t _maxLength{8};
	size_t _length;
	uint8_t _bytes[_maxLength];
	constexpr bool operator==(const Scancode& other) const;
};

constexpr bool Scancode::operator==(const Scancode& other) const
{
	if(_length != other._length)
		return false;
	for(size_t i{0}; i < _length; ++i)
		if(_bytes[i] != other._bytes[i])
			return false;
	return true;
}

}// namespace ps2

#endif// SCANCODE_HPP
