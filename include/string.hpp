#ifndef STRING_HPP
#define STRING_HPP

#include <stddef.h>
#include <kernel/memset.hpp>
#include <kernel/memcpy.hpp>

char *strrchr(const char *, int);
size_t strlen(const char *); 

#endif// STRING_HPP
