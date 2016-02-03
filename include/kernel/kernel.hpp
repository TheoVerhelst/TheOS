#ifndef KERNEL_HPP
#define KERNEL_HPP

#include <stddef.h>
#include <stdint.h>
#include <memory.hpp>

//Forward declarations
struct MultibootInfo;
struct MemoryRegion;

constexpr size_t logKernelHeapSize{20UL};

constexpr size_t kernelHeapSize{1UL << logKernelHeapSize};

MemoryManager kernelHeapMamanger;

extern "C" void kernel_main(const MultibootInfo& info);

void initKernelHeap(MemoryRegion* address, size_t size);

void printDeviceInfo(uint32_t boot_device);

#endif// KERNEL_HPP
