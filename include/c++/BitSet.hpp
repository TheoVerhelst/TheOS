#ifndef BITSET_HPP
#define BITSET_HPP

#include <cstddef>
#include <cstdint>

/// Holds statically a set of boolean values, by using unsigned arithmetic to
/// store them efficiently. This class behaves like std::bitset, and is part of
/// the pseudo-implementation of the standard C++ library.
/// \tparam N The number of values to store (the number of bit).
template <size_t N>
class BitSet
{
	public:

		/// Constructor.
		BitSet();

		/// Set all bits to 1.
		/// \post all()
		void set();

		/// Set the given bit to \a value.
		/// \post test(index) == value
		/// \param index The index of the bit to set.
		/// \param value The value to put at \a index.
		void set(size_t index, bool value = true);

		/// Reset all bits to 0.
		/// \post none()
		void reset();

		/// Reset the given bit to 0.
		/// \post not test(index)
		/// \param index The index of the bit to reset.
		void reset(size_t index);

		/// Flip all bits.
		void flip();

		/// Flip the given bit.
		/// \param index The index of the bit to flip.
		void flip(size_t index);

		/// Checks if none of the bits are set.
		/// \return not any()
		bool none() const;

		/// Checks if any of the bits are set.
		/// \return true if any of the bits are set, false otherwise.
		bool any() const;

		/// Checks if all bits are set.
		/// \return True if all bits are set, false otherwise.
		bool all() const;

		/// Get the value of the given bit.
		/// \param index The index of the bit to check.
		/// \return True if the bit is set, false otherwise.
		bool test(size_t index) const;

		/// Get the index of the first bit with the value \a value.
		/// \param value The value that must have the bit to find.
		/// \return The index of the first bit with the value \a value, or
		/// ~0UL if no bits have the given value.
		size_t find(bool value);

	private:
		/// The size of a word. A word is a number used internally that will be
		/// modified and accessed bitwise. So since we use an unsigned integer
		/// type of 8 bytes, the number of bits in a word is 64.
		static constexpr size_t _wordsSize = 64;

		/// The number of words needed to have at least N bits.
		static constexpr size_t _wordsNumber = (N - 1) / 64 + 1;

		/// The bits, stocked as an array of words.
		uint64_t _words[_wordsNumber];

		/// An index pointing to the last element reached in a call to find().
		/// It is useful because a common use case of a BitSet is to
		/// repeatitively call find() and then set the result, so this variable
		/// avoid a lot of useless tests.
		size_t _lastIndex = 0;
};

template <size_t N>
BitSet<N>::BitSet()
{
	reset();
}

template <size_t N>
void BitSet<N>::set()
{
	for(size_t i{0}; i < _wordsNumber; ++i)
		_words[i] = ~UINT64_C(0);
}

template <size_t N>
void BitSet<N>::set(size_t index, bool value)
{
	if(value)
		_words[index / _wordsSize] |= UINT64_C(1) << (index % _wordsSize);
	else
		reset(index);
}

template <size_t N>
void BitSet<N>::reset()
{
	for(size_t i{0}; i < _wordsNumber; ++i)
		_words[i] = UINT64_C(0);
}

template <size_t N>
void BitSet<N>::reset(size_t index)
{
	_words[index / _wordsSize] &= ~ (UINT64_C(1) << (index % _wordsSize));
}

template <size_t N>
void BitSet<N>::flip()
{
	for(size_t i{0}; i < _wordsNumber; ++i)
		_words[i] = ~ _words[i];
}

template <size_t N>
void BitSet<N>::flip(size_t index)
{
	_words[index / _wordsSize] ^= ~ (UINT64_C(1) << (index % _wordsSize));
}

template <size_t N>
bool BitSet<N>::none() const
{
	return not any();
}

template <size_t N>
bool BitSet<N>::any() const
{
	for(size_t i{0}; i < _wordsNumber; ++i)
		if(_words[i])
			return true;
	return false;
}

template <size_t N>
bool BitSet<N>::all() const
{
	for(size_t i{0}; i < _wordsNumber; ++i)
		if(_words[i] != ~UINT64_C(0))
			return false;
	return true;
}

template <size_t N>
bool BitSet<N>::test(size_t index) const
{
	return _words[index / _wordsSize] & (UINT64_C(1) << (index % _wordsSize));
}

template <size_t N>
size_t BitSet<N>::find(bool value)
{
	const size_t firstTry{_lastIndex};
	do
		if(test(_lastIndex) == value)
			return _lastIndex;
		else
			_lastIndex = (_lastIndex + 1) % N;
	while(_lastIndex != firstTry);
	return ~0UL;
}

#endif// BITSET_HPP
