#include <cpp/abort.hpp>
#include <kernel/Icxxabi.hpp>

extern "C"
{

void __cxa_pure_virtual()
{
	abort("Pure virtual function called");
}

} // extern "C"
