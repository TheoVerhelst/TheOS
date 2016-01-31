#ifndef STRING_HPP
#define STRING_HPP

#include <stddef.h>
#include <stdint.h>

char *strrchr(const char *, int);
size_t strlen(const char *);
char* strcpy(char* dest, const char * src);

void *memsetb(void *, uint8_t, size_t);
void *memsetw(void *, uint16_t, size_t);
void *memsetd(void *, uint32_t, size_t);

void *memcpy(void *, const void *, size_t);


#endif// STRING_HPP
