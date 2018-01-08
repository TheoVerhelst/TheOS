#ifndef MEMORYMAP_HPP
#define MEMORYMAP_HPP

#include <std/cstddef>
#include <boot/MultibootInfo.hpp>

struct MemoryRegion
{
	void* address;
	size_t size;
};

class MemoryMapIterator
{
	public:
		/// Default constructor, makes a valid past-the-end iterator.
		MemoryMapIterator();

		/// Constructor.
		explicit MemoryMapIterator(const multiboot::MemoryRegion* multibootRegion, uintptr_t memoryMapUpperBound);

		MemoryMapIterator(const MemoryMapIterator& other) = default;

		const MemoryRegion& operator*() const;
		const MemoryRegion* operator->() const;
		MemoryMapIterator& operator++();
		MemoryMapIterator operator++(int);
		bool operator==(const MemoryMapIterator& other) const;
		bool operator!=(const MemoryMapIterator& other) const;

	private:
		bool isValid() const;
		void advance();
		void advanceUntilValid();
		void assignFromMultibootRegion();

		const multiboot::MemoryRegion* _multibootRegion;
		uintptr_t _memoryMapUpperBound;
		MemoryRegion _region;
};

class MemoryMap
{
	public:
		typedef MemoryMapIterator ConstIterator;

		/// Constructor.
		MemoryMap(const multiboot::MultibootInfo& multibootInfo);

		ConstIterator begin() const;
		ConstIterator end() const;

	private:
		const multiboot::MemoryRegion* _multibootMemoryMap;
		const uintptr_t _multibootMemoryMapUpperBound;
};

#endif // MEMORYMAP_HPP
