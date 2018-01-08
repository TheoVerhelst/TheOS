#include <cpp/log.hpp>
#include <cpp/abort.hpp>

void abort(const char* message)
{
	LOG(Severity::Error) << (message == nullptr ? "Aborting..." : message);
	while(true);
}
