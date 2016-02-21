#include <kernel/ps2/ScancodeSequence.hpp>

namespace ps2
{

bool ScancodeSequence::operator==(const ScancodeSequence& other) const
{
	if(_length != other._length)
		return false;
	for(size_t i{0}; i < _length; ++i)
		if(_scancodes[i] != other._scancodes[i])
			return false;
	return true;
}

}// namespace ps2
