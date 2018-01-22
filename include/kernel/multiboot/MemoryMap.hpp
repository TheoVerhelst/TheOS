#ifndef MEMORYMAP_HPP
#define MEMORYMAP_HPP

#include <std/cstddef>
#include <kernel/multiboot/MultibootInfo.hpp>

/// Contains structs related to the Multiboot Specification version 0.6.96,
/// which is applied by the bootloader used by the kernel.
namespace multiboot
{

/// This class holds data representing a memory region. Its name is used to
/// distinguish it from multiboot::MemoryRegion, which is the data structure as
/// stated by multiboot specification (and this latter is way more complicated
/// to handle).
struct SimpleMemoryRegion
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

		const SimpleMemoryRegion& operator*() const;
		const SimpleMemoryRegion* operator->() const;
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
		SimpleMemoryRegion _region;
};

/// Class that helps iterate on the memory map given by the multiboot loader.
/// The one given by the bootloader is a pain to iterate on, due to strange
/// storage scheme. This class abstracts that suffering away, by giving a nice
/// iterator-based interface.
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

} // namespace multiboot

#endif // MEMORYMAP_HPP
