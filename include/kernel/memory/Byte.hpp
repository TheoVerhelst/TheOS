#ifndef BYTE_HPP
#define BYTE_HPP

/// \addtogroup Kernel
/// \{

// TODO save as kernel/config.hpp

typedef unsigned char Byte;

constexpr size_t addressSize{sizeof(void*) * 8};

/// The size of a frame of a page, in bytes.
constexpr size_t frameSize{4096};

/// \}

#endif// BYTE_HPP
