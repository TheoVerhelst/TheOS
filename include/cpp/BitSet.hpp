#ifndef BITSET_HPP
#define BITSET_HPP

#include <std/cstddef>
#include <std/cstdint>

/// Holds statically a set of boolean values, by using unsigned arithmetic to
/// store them efficiently. This class behaves like std::bitset, and is part of
/// the pseudo-implementation of the standard C++ library.
/// \tparam N The number of values to store (the number of bits).
template <size_t N>
class BitSet
{
	public:
		size_t _invalidIndex{~0UL};

		/// Constructor.
		/// \param value The value to set to every bit of the bitset.
		BitSet(bool value = false);

		/// Sets all bits to 1.
		/// \post all()
		void set();

		/// Sets the given bit to \a value.
		/// \post test(index) == value
		/// \param index The index of the bit to set.
		/// \param value The value to put at \a index.
		void set(size_t index, bool value = true);

		/// Resets all bits to 0.
		/// \post none()
		void reset();

		/// Resets the given bit to 0.
		/// \post not test(index)
		/// \param index The index of the bit to reset.
		void reset(size_t index);

		/// Flips all bits.
		void flip();

		/// Flips the given bit.
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

		/// Gets the value of the given bit.
		/// \param index The index of the bit to check.
		/// \return True if the bit is set, false otherwise.
		bool test(size_t index) const;

		/// Gets the index of the first bit with the value \a value.
		/// \param value The value that must have the bit to find.
		/// \return The index of the first bit with the value \a value, or
		/// invalidIndex if no bits have the given value.
		size_t find(bool value) const;

		/// Gets the size of the bitset, its number of bits.
		/// \return The number of bits in the bitset.
		constexpr size_t size() const;

	private:
		/// The size of a word. A word is a number used internally that will be
		/// modified and accessed bitwise.
		static constexpr size_t _wordSize = sizeof(uintmax_t) * 8;

		/// The number of words needed to have at least N bits.
		static constexpr size_t _wordsNumber = (N == 0 ? 0 :((N - 1) / _wordSize) + 1);

		static constexpr uintmax_t _zero{UINTMAX_C(0)};

		static constexpr uintmax_t _one{UINTMAX_C(1)};

		/// The bits, stocked as an array of words.
		uintmax_t _words[_wordsNumber];
};

#include <cpp/math.hpp>

template <size_t N>
BitSet<N>::BitSet(bool value)
{
	if(value)
		set();
	else
		reset();
}

template <size_t N>
void BitSet<N>::set()
{
	for(auto& word : _words)
		word = ~_zero;
}

template <size_t N>
void BitSet<N>::set(size_t index, bool value)
{
	if(value)
		_words[index / _wordSize] |= _one << (index % _wordSize);
	else
		_words[index / _wordSize] &= ~ (_one << (index % _wordSize));
}

template <size_t N>
void BitSet<N>::reset()
{
	for(auto& word : _words)
		word = _zero;
}

template <size_t N>
void BitSet<N>::reset(size_t index)
{
	set(index, false);
}

template <size_t N>
void BitSet<N>::flip()
{
	for(auto& word : _words)
		word = ~word;
}

template <size_t N>
void BitSet<N>::flip(size_t index)
{
	_words[index / _wordSize] ^= ~ (_one << (index % _wordSize));
}

template <size_t N>
bool BitSet<N>::none() const
{
	return not any();
}

template <size_t N>
bool BitSet<N>::any() const
{
	for(auto& word : _words)
		if(word != _zero)
			return true;
	return false;
}

template <size_t N>
bool BitSet<N>::all() const
{
	for(auto& word : _words)
		if(word != ~_zero)
			return false;
	return true;
}

template <size_t N>
bool BitSet<N>::test(size_t index) const
{
	return _words[index / _wordSize] & (_one << (index % _wordSize));
}

template <size_t N>
size_t BitSet<N>::find(bool value) const
{
	for(size_t i{0}; i < N; ++i)
	{
		if(test(i) == value)
			return i;
	}
	return _invalidIndex;
}

template <size_t N>
constexpr size_t BitSet<N>::size() const
{
	return N;
}

#endif // BITSET_HPP
