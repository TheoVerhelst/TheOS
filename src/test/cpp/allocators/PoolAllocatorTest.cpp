#include <vector>
#include <unordered_set>
#include <test/catch/catch.hpp>
#include <cpp/allocators/PoolAllocator.hpp>

SCENARIO("Pool allocator returns nullptr when full")
{
    GIVEN("A fresh PoolAllocator")
    {
		constexpr size_t size{8};
		Pool<int, size> pool;
		PoolAllocator<int, size> allocator{pool};

		WHEN("Ints are allocated repeatedly")
		{
			std::vector<int*> addresses;
			for(size_t i{0}; i < size + 1; ++i)
				addresses.push_back(allocator.allocate());

            THEN("All 8 addresses are different")
            {
                std::unordered_set<int*> addressesSet(addresses.begin(), addresses.end());
                REQUIRE(addresses.size() == addressesSet.size());
            }

			THEN("The last address is nullptr")
				REQUIRE(addresses.back() == nullptr);
		}
	}
}

SCENARIO("Allocated addresses are in the address range of the pool")
{
	GIVEN("A fresh PoolAllocator")
	{
		constexpr size_t size{8};
		Pool<int, size> pool;
		PoolAllocator<int, size> allocator{pool};

		WHEN("Some ints are allocated")
		{
			int* first{allocator.allocate()};
			int* second{allocator.allocate()};

			THEN("Both addresses lie in the range of the pool address")
			{
				const uintptr_t firstAddress{reinterpret_cast<uintptr_t>(first)};
				const uintptr_t secondAddress{reinterpret_cast<uintptr_t>(second)};
				const uintptr_t poolBegin{reinterpret_cast<uintptr_t>(&pool)};
				const uintptr_t poolEnd{reinterpret_cast<uintptr_t>(&pool) + sizeof(pool)};
				REQUIRE(firstAddress >= poolBegin);
                REQUIRE(firstAddress < poolEnd);
				REQUIRE(secondAddress >= poolBegin);
                REQUIRE(secondAddress < poolEnd);
			}
		}
	}
}
