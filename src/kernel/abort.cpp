#include <Printer.hpp>
#include <kernel/abort.hpp>

void abort(const char* message)
{
	if(message == nullptr)
		out << "Aborting...";
	else
		out << message;
	while(true);
}
