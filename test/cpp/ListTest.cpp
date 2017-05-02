#include <catch/catch.hpp>
#include <cpp/List.hpp>

template <typename T>
void requireListIsEmpty(const List<T>& list)
{
    REQUIRE(list.size() == 0);
    REQUIRE(list.empty());
    REQUIRE(list.begin() == list.end());
}

SCENARIO("Empty list")
{
    GIVEN("A default-constructed list")
    {
        List<double> list;
        THEN("list is empty")
            requireListIsEmpty(list);

        WHEN("an elements is appended")
        {
            list.pushBack(3.41);
            THEN("size is equal to one")
            {
                REQUIRE(list.size() == 1);
                REQUIRE_FALSE(list.empty());
                REQUIRE(list.begin() != list.end());
            }

            THEN("front() is the added element")
                REQUIRE(list.front() == 3.41);

            WHEN("the element is removed")
            {
                list.erase(list.begin());
                THEN("list is empty")
                    requireListIsEmpty(list);
            }
        }

        WHEN("Four elements are appended")
        {
            list.pushBack(2);
            list.pushBack(3);
            list.pushBack(5);
            list.pushBack(8);

            THEN("The size is four")
                REQUIRE(list.size() == 4);

            THEN("All elements are in the list")
            {
                auto it(list.begin());
                for(auto value : {2, 3, 5, 8})
                    REQUIRE(*(it++) == value);
            }

            WHEN("The list is copy-constructed")
            {
                List<double> other(list);

                THEN("The size is four")
                    REQUIRE(other.size() == 4);

                THEN("All elements are in the list")
                {
                    auto it(other.begin());
                    for(auto value : {2, 3, 5, 8})
                        REQUIRE(*(it++) == value);
                }
            }
        }
    }
}
