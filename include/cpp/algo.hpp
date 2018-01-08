#ifndef ALGO_HPP
#define ALGO_HPP

namespace algo
{

template <typename InputIt, typename Predicate>
InputIt find(InputIt begin, InputIt end, const Predicate& predicate);

} // namespace algo

namespace algo
{
    template <typename InputIt, typename Predicate>
    InputIt find(InputIt begin, InputIt end, const Predicate& predicate)
    {
        while(begin != end and not predicate(*begin))
            ++begin;
        return begin;
    }
} // namespace algo

#endif // ALGO_HPP
