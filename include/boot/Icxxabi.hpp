#ifndef ICXXABI_HPP
#define ICXXABI_HPP

extern "C"
{

/// Function called when a pure virtual function is called. It aborts with an
/// error message.
void __cxa_pure_virtual();

} // extern "C"



#endif // ICXXABI_HPP
