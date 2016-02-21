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
	bool operator==(const ScancodeSequence& other) const;
};

}// namespace ps2

#endif// SCANCODESEQUENCE_HPP
