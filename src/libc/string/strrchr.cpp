#include <string.hpp>

char *strrchr(const char *str, int c)
{
	size_t length = strlen(str);
	while(length > 0 && str[length] != c)
		--length;
	if(str[length] == c)
		return const_cast<char*>(&str[length]);
	else
		return NULL;
}

