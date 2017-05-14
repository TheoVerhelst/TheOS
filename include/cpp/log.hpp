#ifndef LOG_HPP
#define LOG_HPP

#include <cpp/Printer.hpp>

enum class Severity
{
	Info,
	Warning,
	Error
};

Printer& operator<<(Printer& printer, const Severity& severity);

#define LOG(severity) out << "[" << severity << "] " << __func__ << ": "

#define STOP() out << "Stopped at " << __func__ << " (" << __FILE__ << ":" << __LINE__ << ")\n"; while(true);

#endif // LOG_HPP
