#ifndef SCANCODESEQUENCE_HPP
#define SCANCODESEQUENCE_HPP

#include <cstddef>
#include <cstdint>

namespace ps2
{

struct ScancodeSequence
{
	static constexpr size_t _maxLength{6};
	size_t _length;
	uint8_t _scancodes[_maxLength];
	constexpr bool operator==(const ScancodeSequence& other) const;
};

constexpr bool ScancodeSequence::operator==(const ScancodeSequence& other) const
{
	if(_length != other._length)
		return false;
	for(size_t i{0}; i < _length; ++i)
		if(_scancodes[i] != other._scancodes[i])
			return false;
	return true;
}

}// namespace ps2

#endif// SCANCODESEQUENCE_HPP
