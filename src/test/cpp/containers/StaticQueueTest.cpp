#include <test/catch/catch.hpp>
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
        static constexpr size_t queueSize{16};
        StaticQueue<double, queueSize> queue;
        THEN("queue is empty")
            requireQueueIsEmpty(queue);

        WHEN("an element is pushed")
        {
            double value{3.41};
            queue.pushBack(value);
            THEN("size is equal to one")
            {
                REQUIRE(queue.size() == 1);
                REQUIRE_FALSE(queue.empty());
                REQUIRE(queue.begin() != queue.end());
            }

            THEN("front() is the added element")
                REQUIRE(queue.front() == value);

            WHEN("the element is removed")
            {
                double poppedValue{queue.popFront()};
                THEN("The popped element is the added one")
					REQUIRE(poppedValue == value);
                THEN("queue is empty")
                    requireQueueIsEmpty(queue);
            }
        }

        WHEN("Four elements are appended")
        {
            std::vector<double> values{2, 3, 5, 8};
            for(auto& value : values)
                queue.pushBack(value);

            THEN("The size is four")
                REQUIRE(queue.size() == values.size());

            THEN("All elements are in the queue")
            {
                auto it(queue.begin());
                for(auto& value : values)
                    REQUIRE(*(it++) == value);
            }

            WHEN("The queue is copy-constructed")
            {
                StaticQueue<double, queueSize> other(queue);

                THEN("The size is four")
                    REQUIRE(other.size() == values.size());

                THEN("All elements are in the queue")
                {
                    auto it(other.begin());
                    for(auto& value : values)
                        REQUIRE(*(it++) == value);
                }
            }
        }

        WHEN("The queue is full")
        {
            // Only 15 elements, see StaticQueue doc
            std::vector<double> values{5., 88., 4., 6., 5., 8., 4., 6., 5., 8., 4., 6., 5., 8., 4.};
            for(double v : values)
                queue.pushBack(v);

            THEN("The size no longer increases")
            {
                size_t oldSize{queue.size()};
                queue.pushBack(54);
                REQUIRE(queue.size() == oldSize);
                REQUIRE(queue.size() == queueSize - 1);
            }

            THEN("The first element is erased")
            {
                double value{43.};
                queue.pushBack(value);
                REQUIRE(queue.front() == values[1]);
                REQUIRE(queue.back() == value);
            }

            WHEN("The queue is cleared")
            {
                queue.clear();
                THEN("The queue is empty")
                    requireQueueIsEmpty(queue);
            }
        }
    }
}
