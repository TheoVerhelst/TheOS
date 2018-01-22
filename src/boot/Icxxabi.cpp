#include <cpp/abort.hpp>
#include <boot/Icxxabi.hpp>

extern "C"
{

void __cxa_pure_virtual()
{
	abort("Pure virtual function called");
}

} // extern "C"
