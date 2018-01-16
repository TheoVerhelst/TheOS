#include <cpp/string.hpp>

namespace str
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

char* concat(char* dest, const char* src, size_t n)
{
	if(n != 0)
	{
		char *d = dest;
		const char *s = src;

		while (*d != 0)
			d++;
		do
		{
			*d = *s++;
			if(*d == 0)
				break;
			d++;
		} while (--n != 0);
		*d = 0;
	}
	return dest;
}

} // namespace string
