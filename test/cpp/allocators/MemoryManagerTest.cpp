#include <cmath>
#include <cstdint>
#include <catch/catch.hpp>
#include <cpp/allocators/MemoryManager.hpp>

SCENARIO("Memory manager tests")
{
    GIVEN("A fresh MemoryManager")
    {
        constexpr size_t bufferSize{512}; // Arbitrary size
        char buffer[bufferSize];
        MemoryManager manager{buffer, bufferSize};
        WHEN("Two regions are allocated")
        {
            constexpr size_t firstAskedSize{13}; // Arbitrary size
            constexpr size_t secondAskedSize{30}; // Arbitrary size
            void* first{manager.allocate(firstAskedSize)};
            void* second{manager.allocate(secondAskedSize)};

            THEN("The regions have different addresses")
                REQUIRE(first != second);

            THEN("nullptr is not returned")
                REQUIRE(first != nullptr);

            WHEN("The first region is freed, and another allocation is requested")
            {
                manager.deallocate(first);
                void* third{manager.allocate(firstAskedSize)};
                THEN("The new region is at the same place as the first")
                    REQUIRE(first == third);
            }
        }

        WHEN("A really big region is requested")
        {
            constexpr size_t bigRequestedSize{bufferSize + 1};
            void* allocated{manager.allocate(bigRequestedSize)};
            THEN("The returned address is nullptr")
                REQUIRE(allocated == nullptr);
        }

        WHEN("Two equal regions are requested")
        {
            constexpr size_t requestedSize{64};
            void* first{manager.allocate(requestedSize)};
            void* second{manager.allocate(requestedSize)};
            THEN("The two regions are spaced at least by the requested size")
                REQUIRE(std::abs(reinterpret_cast<std::intptr_t>(first) - reinterpret_cast<std::intptr_t>(second))
                        >= requestedSize);
        }
    }
}
