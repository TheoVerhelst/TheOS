#include <cpp/log.hpp>

Printer& operator<<(Printer& printer, const Severity& severity)
{
	switch(severity)
	{
		case Severity::Info:
			return printer << "Info";

		case Severity::Warning:
			return printer << "Warning";

		case Severity::Error:
		default:
			return printer << "Error";
	}
}
