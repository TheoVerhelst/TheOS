#ifndef ABORT_HPP
#define ABORT_HPP

/// Aborts the kernel (enters in an infinite loop).
[[noreturn]] void abort(const char* message = nullptr);

#endif// ABORT_HPP
