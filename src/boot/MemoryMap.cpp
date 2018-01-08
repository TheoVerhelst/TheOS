#include <boot/MemoryMap.hpp>

MemoryMapIterator::MemoryMapIterator():
	_multibootRegion{nullptr},
	_memoryMapUpperBound{0UL}
{
}

MemoryMapIterator::MemoryMapIterator(const multiboot::MemoryRegion* multibootRegion, uintptr_t memoryMapUpperBound):
	_multibootRegion{multibootRegion},
	_memoryMapUpperBound{memoryMapUpperBound}
{
	assignFromMultibootRegion();
	advanceUntilValid();
}

const MemoryRegion& MemoryMapIterator::operator*() const
{
	return _region;
}

const MemoryRegion* MemoryMapIterator::operator->() const
{
	return &_region;
}

MemoryMapIterator& MemoryMapIterator::operator++()
{
	advance();
	advanceUntilValid();
	return *this;
}

MemoryMapIterator MemoryMapIterator::operator++(int)
{
	MemoryMapIterator selfCopy{*this};
	++(*this);
	return selfCopy;
}

bool MemoryMapIterator::operator==(const MemoryMapIterator& other) const
{
	return _multibootRegion == other._multibootRegion;
}

bool MemoryMapIterator::operator!=(const MemoryMapIterator& other) const
{
	return not (*this == other);
}

bool MemoryMapIterator::isValid() const
{
	// past-the-end iterator is a valid one
	return _multibootRegion == nullptr or _multibootRegion->type == multiboot::MemoryRegion::validType;
}

void MemoryMapIterator::advanceUntilValid()
{
	while(not isValid())
		advance();
}

void MemoryMapIterator::advance()
{
	uintptr_t uintAddress{reinterpret_cast<uintptr_t>(_multibootRegion)};
	uintAddress += _multibootRegion->size + sizeof(_multibootRegion->size);
	_multibootRegion = reinterpret_cast<multiboot::MemoryRegion*>(uintAddress);

	if(uintAddress >= _memoryMapUpperBound)
		// Assign a default-constructed (past-the-end) iterator to itself
		*this = MemoryMapIterator();
	else
		assignFromMultibootRegion();
}

void MemoryMapIterator::assignFromMultibootRegion()
{
	_region = {reinterpret_cast<void*>(_multibootRegion->base_addr & UINT64_C(0xFFFFFFFF)),
			   static_cast<size_t>(_multibootRegion->length)};
}

MemoryMap::MemoryMap(const multiboot::MultibootInfo& multibootInfo):
	_multibootMemoryMap{multibootInfo.mmap_addr},
	_multibootMemoryMapUpperBound{reinterpret_cast<uintptr_t>(_multibootMemoryMap) + multibootInfo.mmap_length}
{
}

MemoryMap::ConstIterator MemoryMap::begin() const
{
	return ConstIterator(_multibootMemoryMap, _multibootMemoryMapUpperBound);
}

MemoryMap::ConstIterator MemoryMap::end() const
{
	return ConstIterator();
}
