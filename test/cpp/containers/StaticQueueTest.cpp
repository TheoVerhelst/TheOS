#include <catch/catch.hpp>
#include <cpp/containers/StaticQueue.hpp>

template <typename T, size_t MaxSize>
void requireQueueIsEmpty(const StaticQueue<T, MaxSize>& queue)
{
    REQUIRE(queue.size() == 0);
    REQUIRE(queue.empty());
    REQUIRE(queue.begin() == queue.end());
}

SCENARIO("Empty queue")
{
    GIVEN("A default-constructed queue")
    {
        StaticQueue<double, 16> queue;
        THEN("queue is empty")
            requireQueueIsEmpty(queue);

        WHEN("an elements is pushed")
        {
            queue.pushBack(3.41);
            THEN("size is equal to one")
            {
                REQUIRE(queue.size() == 1);
                REQUIRE_FALSE(queue.empty());
                REQUIRE(queue.begin() != queue.end());
            }

            THEN("front() is the added element")
                REQUIRE(queue.front() == 3.41);

            WHEN("the element is removed")
            {
                double poppedValue{queue.popFront()};
                THEN("The popped element is the added one")
					REQUIRE(poppedValue == 3.41);
                THEN("queue is empty")
                    requireQueueIsEmpty(queue);
            }
        }

        WHEN("Four elements are appended")
        {
            queue.pushBack(2);
            queue.pushBack(3);
            queue.pushBack(5);
            queue.pushBack(8);
            THEN("The size is four")
                REQUIRE(queue.size() == 4);

            THEN("All elements are in the queue")
            {
                auto it(queue.begin());
                for(auto value : {2, 3, 5, 8})
                    REQUIRE(*(it++) == value);
            }

            WHEN("The queue is copy-constructed")
            {
                StaticQueue<double, 16> other(queue);

                THEN("The size is four")
                    REQUIRE(other.size() == 4);

                THEN("All elements are in the queue")
                {
                    auto it(other.begin());
                    for(auto value : {2, 3, 5, 8})
                        REQUIRE(*(it++) == value);
                }
            }
        }
    }
}
