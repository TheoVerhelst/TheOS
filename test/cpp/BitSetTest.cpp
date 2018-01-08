#include <catch/catch.hpp>
#include <cpp/BitSet.hpp>

template <size_t Size>
void requireBitSetState(const BitSet<Size>& bitset, bool none, bool all, bool any, bool found)
{
        REQUIRE(bitset.none() == none);
        REQUIRE(bitset.all() == all);
        REQUIRE(bitset.any() == any);
        REQUIRE((bitset.find(true) != bitset._invalidIndex) == found);
}

SCENARIO("BitSet with size 20")
{
    constexpr size_t size{20};
    GIVEN("A false-initialized bitset")
    {
        BitSet<size> bitset;

        THEN("It is all false")
            requireBitSetState(bitset, true, false, false, false);

        WHEN("We search for false bit 20 times")
        {
            for(size_t i{0}; i < size; ++i)
            {
                const size_t index{bitset.find(false)};
                THEN("The found index is valid")
                {
                    REQUIRE(index != bitset._invalidIndex);
                    REQUIRE(index < size);
                }
                bitset.set(index);
            }

            WHEN("... and we search for a false bit once again")
            {
                const size_t index{bitset.find(false)};
                THEN("The found index is not valid")
                    REQUIRE(index == bitset._invalidIndex);
            }


        }

        WHEN("A bit is set")
        {
            bitset.set(3);
            THEN("The bit is effectively set")
                REQUIRE(bitset.test(3));
            THEN("The getters reflect the new set bit")
                requireBitSetState(bitset, false, false, true, true);
            THEN("BitSet::find returns the set bit")
                REQUIRE(bitset.find(true) == 3);

            WHEN("The bitset is then flipped")
            {
                bitset.flip();
                THEN("The bit is no longer set")
                    REQUIRE(not bitset.test(3));
                THEN("The getters reflect the flip")
                    requireBitSetState(bitset, false, false, true, true);
            }
        }

        WHEN("The bitset is flipped")
        {
            bitset.flip();
            THEN("All bits are set")
                requireBitSetState(bitset, false, true, true, true);

            WHEN("The bitset is reset")
            {
                bitset.reset();
                THEN("All bits are reset")
                    requireBitSetState(bitset, true, false, false, false);
            }
        }
    }

    GIVEN("A true-initialized bitset")
    {
        BitSet<size> bitset{true};
        THEN("All bits are set")
            requireBitSetState(bitset, false, true, true, true);
    }
}
