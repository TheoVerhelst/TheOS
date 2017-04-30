#include <catch/catch.hpp>
#include <cpp/Array.hpp>

class ConstructionTracer
{
    public:
        bool _hasBeenDefaultConstructed;
        bool _hasBeenIntConstructed;

        ConstructionTracer()
        {
            _hasBeenDefaultConstructed = true;
            _hasBeenIntConstructed = false;
        }

        ConstructionTracer(int)
        {
            _hasBeenIntConstructed = true;
            _hasBeenDefaultConstructed = false;
        }
};

SCENARIO("Array contains values")
{
    GIVEN("An array with integers")
    {
        Array<int, 8> array{12};
        THEN("all elements are equals to 12")
        {
            for(int e : array)
                REQUIRE(e == 12);
        }
    }

    GIVEN("An array with a default-constructed object")
    {
        Array<ConstructionTracer, 1> array;
        THEN("the object has been default-constructed")
        {
            REQUIRE(array[0]._hasBeenDefaultConstructed);
            REQUIRE_FALSE(array[0]._hasBeenIntConstructed);
        }
    }

    GIVEN("An array with an object constructed with integer")
    {
        Array<ConstructionTracer, 1> array{23};
        THEN("the object has been int-constructed")
        {
            REQUIRE(array[0]._hasBeenIntConstructed);
            REQUIRE_FALSE(array[0]._hasBeenDefaultConstructed);
        }
    }
}
