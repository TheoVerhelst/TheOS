#ifndef SCANCODE_HPP
#define SCANCODE_HPP

#include <std/cstddef>
#include <std/cstdint>

namespace ps2
{

struct Scancode
{
	static constexpr size_t maxLength {8};
	size_t length;
	uint8_t bytes[maxLength];
	constexpr bool operator==(const Scancode& other) const;
};

} // namespace ps2

namespace ps2
{

constexpr bool Scancode::operator==(const Scancode& other) const
{
	if(length != other.length)
		return false;
	for(size_t i{0}; i < length; ++i)
		if(bytes[i] != other.bytes[i])
			return false;
	return true;
}

} // namespace ps2



#endif // SCANCODE_HPP
