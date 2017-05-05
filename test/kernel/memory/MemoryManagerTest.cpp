#include <catch/catch.hpp>
#include <kernel/memory/MemoryManager.hpp>

SCENARIO("Allocation reuses previously freed memory")
{
    GIVEN("A fresh MemoryManager")
    {
        constexpr size_t bufferSize{512}; // Arbitrary size
        char buffer[bufferSize];
        MemoryManager manager{buffer, bufferSize};
        WHEN("Two regions are allocated")
        {
            constexpr size_t askedSize{16}; // Arbitrary size
            void* first{manager.allocate(askedSize)};
            void* second{manager.allocate(askedSize)};
            THEN("The regions have different addresses")
                REQUIRE(first != second);

            THEN("nullptr is not returned")
                REQUIRE(first != nullptr);

            WHEN("The first region is freed, and another is allocated again")
            {
                manager.deallocate(first);
                void* third{manager.allocate(askedSize)};
                THEN("The new region is at the same place as the first")
                    REQUIRE(first == third);
            }
        }
    }
}
