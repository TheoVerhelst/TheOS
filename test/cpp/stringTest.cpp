#include <catch/catch.hpp>
#include <cpp/string.hpp>

SCENARIO("Testing string length function")
{
	GIVEN("A C-style string")
	{
		const char* aString{"123456789"};
		THEN("Its computed length is 9")
			REQUIRE(string::length(aString) == 9);
	}

	GIVEN("An empty C-style string")
	{
		const char* aString{""};
		THEN("Its computed length is 0")
			REQUIRE(string::length(aString) == 0);
	}
}

SCENARIO("Testing string copy function")
{
	GIVEN("A C-style string")
	{
		const char* original{"Hi dudes, what are you up to today?"};
		WHEN("The original string is copied")
		{
			char* copy = new char[string::length(original) + 1];
			string::copy(copy, original);
			THEN("Both strings compare equal")
			{
				for(std::size_t i{0}; i < string::length(original); ++i)
					REQUIRE(original[i] == copy[i]);
			}
		}
	}

	GIVEN("An empty C-style string")
	{
		const char* original{""};
		WHEN("The original string is copied")
		{
			char* copy = new char[1];
			string::copy(copy, original);
			THEN("The copied string is also empty")
				REQUIRE(string::length(copy) == 0);
		}
	}
}
