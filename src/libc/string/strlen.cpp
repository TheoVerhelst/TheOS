#include <string.hpp>

extern "C"
{

size_t strlen(const char *s)
{
	size_t length{0};
	while(s[length] != '\0')
		++length;
	return length;
}

}// extern "C"
