#include <math.hpp>

int abs(int n)
{
	return n >= 0 ? n : -n;
}

long int abs(long int n)
{
	return n >= 0L ? n : -n;
}

long long int abs(long long int n)
{
	return n >= 0LL ? n : -n;
}
