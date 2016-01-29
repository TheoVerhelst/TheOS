#ifndef STRING_HPP
#define STRING_HPP

#include <stddef.h>
#include <kernel/_memtypes.hpp>

char *strrchr(const char *, int);
size_t strlen(const char *);

void *memsetb(void *, BYTE, size_t);
void *memsetw(void *, WORD, size_t);
void *memsetd(void *, DWORD, size_t);

void *memcpy(void *, const void *, size_t);


#endif// STRING_HPP
