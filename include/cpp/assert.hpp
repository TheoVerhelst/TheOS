#ifndef ASSERT_HPP
#define ASSERT_HPP

#include <cpp/abort.hpp>

#ifdef NDEBUG
#define ASSERT(expression)
#else
#define ASSERT(expression) static_cast<void>((expression) || (impl::assert(#expression, __FILE__, __LINE__), false))
#endif

namespace impl
{

void assert(const char* expression, const char* filename, int lineNumber);

} // namespace impl

#endif // ASSERT_HPP
