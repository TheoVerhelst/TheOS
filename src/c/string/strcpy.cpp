#include <string.hpp>

extern "C"
{

char* strcpy(char* dest, const char * src)
{
	int i = 0;
	while(src[i] != '\0')
		dest[i] = src[i++];
	dest[i] = '\0';
	return dest;
}

}// extern "C"
