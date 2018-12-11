#include <test/catch/catch.hpp>
#include <cpp/math.hpp>

SCENARIO("Testing abs function")
{
	REQUIRE(math::abs(0) == 0);
	REQUIRE(math::abs(-1) == 1);
	REQUIRE(math::abs(54) == 54);
	REQUIRE(math::abs(-23) == 23);
}

SCENARIO("Testing log2 function")
{
	// As stated in the documentation, log2(0) returns 0
	REQUIRE(math::log2(0u) == 0u);
	REQUIRE(math::log2(-0u) == 0u);
	REQUIRE(math::log2(1u) == 0u);
	REQUIRE(math::log2(2u) == 1u);
	REQUIRE(math::log2(3u) == 1u);
	REQUIRE(math::log2(4u) == 2u);
	REQUIRE(math::log2(1023u) == 9u);
	REQUIRE(math::log2(1024u) == 10u);
	REQUIRE(math::log2(1025u) == 10u);
}

SCENARIO("Testing min and max functions")
{
	REQUIRE(math::min(-43, -4) == -43);
	REQUIRE(math::min(0, -4) == -4);
	REQUIRE(math::min(43, 4) == 4);
	REQUIRE(math::max(-43, -4) == -4);
	REQUIRE(math::max(0, -4) == 0);
	REQUIRE(math::max(43, 4) == 43);
}
