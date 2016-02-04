#ifndef STRING_HPP
#define STRING_HPP

#include <stddef.h>
#include <stdint.h>

extern "C"
{

char *strrchr(const char *, int);
size_t strlen(const char *);
char* strcpy(char* dest, const char * src);
void *memset(void *, int, size_t);
void *memcpy(void *, const void *, size_t);

}// extern "C"

void *_memset(void *, uint8_t, size_t);
void *_memset(void *, uint16_t, size_t);
void *_memset(void *, uint32_t, size_t);

#endif// STRING_HPP
