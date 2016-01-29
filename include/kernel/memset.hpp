#ifndef MEMSET_HPP
#define MEMSET_HPP

#include <stddef.h>
#include <kernel/_memtypes.hpp>

void *memsetb(void *, BYTE, size_t);
void *memsetw(void *, WORD, size_t);
void *memsetd(void *, DWORD, size_t);

#endif// MEMSET_HPP
