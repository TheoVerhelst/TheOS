#ifndef MEMORYMAPBROWSER_HPP
#define MEMORYMAPBROWSER_HPP

#include <cstddef>
#include <kernel/memory/Byte.hpp>
#include <boot/MultibootInfo.hpp>
#include <List.hpp>
#include <kernel/memory/PoolAllocator.hpp>

/// Browse the memory map given by the boot loader and give the address
/// of a region	that have the needed size, and manage the memory map
/// so that no memory region is wasted.
class MemoryMapBrowser
{
	public:
		/// The maximum number of memory regions that this class will be able
		/// to manage. The value is arbitrary, and should reflects the number
		/// of elements in the multiboot memory map.
		static constexpr size_t _memoryRegionNumber{16};

		struct MemoryRegion
		{
			Byte* _address;
			size_t _size;
		};

		typedef PoolAllocator<details::ListNode<MemoryRegion>, _memoryRegionNumber> RegionsAllocator;

		typedef typename List<MemoryRegion, RegionsAllocator>::iterator Iterator;

		typedef typename List<MemoryRegion, RegionsAllocator>::constIterator ConstIterator;

		/// Default constructor. It expects that multiboot::multibootInfoAddress
		/// is available for use.
		MemoryMapBrowser();

		/// Gives the address of the beginning of a memory region
		/// that have the size \a neededRegionSize.
		/// \param neededRegionSize The size that the returned region must have.
		/// \return The base address of a memory region of size \a neededRegionSize,
		/// or nullptr in case of failure.
		Byte* findMemoryRegion(size_t neededRegionSize);

		Iterator begin();

		ConstIterator cbegin() const;

		Iterator end();

		ConstIterator cend() const;

	private:
		RegionsAllocator::PoolType _memoryRegionsPool;

		List<MemoryRegion, RegionsAllocator> _memoryRegions;
};

#endif// MEMORYMAPBROWSER_HPP
