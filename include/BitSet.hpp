#ifndef BITSET_HPP
#define BITSET_HPP

#include <stddef.h>
#include <stdint.h>

template <size_t N>
class BitSet
{
	public:
		BitSet();
		void set();
		void set(size_t index, bool value = true);
		void reset();
		void reset(size_t index);
		void flip();
		void flip(size_t index);
		bool none() const;
		bool any() const;
		bool all() const;
		bool test(size_t index) const;
		size_t find(bool value);

	private:
		static constexpr size_t _wordsSize = 64;
		static constexpr size_t _wordsNumber = (N - 1) / 64 + 1;
		uint64_t _words[_wordsNumber];
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
