#include <cpp/abort.hpp>
#include <cpp/string.hpp>
#include <cpp/assert.hpp>

namespace impl
{

void assert(const char* expression, const char* filename, int lineNumber)
{
	// Arbitrary lengths, we can't afford dynamic allocation here
	char errorString[512];
	char lineNumberStr[8];
	str::toString(lineNumberStr, sizeof(lineNumberStr), lineNumber);

	const char* toConcat[] = {"Assertion failed:", expression, "at", filename, ", line", lineNumberStr};
	for(auto& string : toConcat)
		str::concat(errorString, string, sizeof(errorString) - str::length(string) - 1);

	abort(errorString);
}

} // namespace impl
