#include <string.hpp>

namespace string
{

size_t length(const char *s)
{
	size_t length{0};
	while(s[length] != '\0')
		++length;
	return length;
}

char* copy(char* dest, const char * src)
{
	size_t i{0};
	while(src[i] != '\0')
	{
		dest[i] = src[i];
		++i;
	}
	dest[i] = '\0';
	return dest;
}

}
