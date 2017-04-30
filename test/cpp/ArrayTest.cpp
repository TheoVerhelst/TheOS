#include <catch/catch.hpp>
#include <Array.hpp>

class ConstructionTracer
{
    public:
        static bool _hasBeenDefaultConstructed = false;
        static bool _hasBeenIntConstructed = false;

        ConstructionTracer()
        {
            _defaultConstructed = true;
        }

        ConstructionTracer(int)
        {
            _intConstructed = true;
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
                REQUIRE(e = 12);
        }
    }

    GIVEN("An array with a default-constructed object")
    {
        Array<ConstructionTracer, 1> array;
        THEN("the object has been default-constructed")
        {
            REQUIRE(ConstructionTracer::_hasBeenDefaultConstructed);
        }
    }

    GIVEN("An array with an object constructed with integer")
    {
        Array<ConstructionTracer, 1> array{23};
        THEN("the object has been int-constructed")
        {
            REQUIRE(ConstructionTracer::_hasBeenIntConstructed);
        }
    }
}
