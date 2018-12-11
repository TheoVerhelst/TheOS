#include <test/catch/catch.hpp>
#include <cpp/flags.hpp>

enum TestFlags : unsigned int
{
	First  = 1 << 0,
	Second = 1 << 1,
	Third  = 1 << 2
};

SCENARIO("Testing allSet function")
{
	REQUIRE(not flags::allSet(0b0010u, TestFlags::First | TestFlags::Second | TestFlags::Third));
	REQUIRE(flags::allSet(0b0111u, TestFlags::First | TestFlags::Second | TestFlags::Third));
	REQUIRE(not flags::allSet(0b1010u, TestFlags::First | TestFlags::Second | TestFlags::Third));
	REQUIRE(flags::allSet(0b1111u, TestFlags::First | TestFlags::Second | TestFlags::Third));
	REQUIRE(flags::allSet(0b1111u, 0u));
}
