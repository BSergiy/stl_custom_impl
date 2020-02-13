#include <iostream>
#include <set>
#include <cassert>

#include "set.hpp"

template <typename T = uint64_t,
        size_t size = 1000,
        typename t_cmp = t_std::less<>,
        typename cmp = std::less<>>
void test_set_with_options()
{
    t_std::set<T, t_cmp> s1;
    std::set<T, cmp> s2;

    srand (time(0));
    for (size_t i = 0; i < size; ++i)
    {
        auto val = rand() % size;
        s1.emplace(val);
        s2.emplace(val);
    }

    auto it1 = s1.begin();
    auto it2 = s2.begin();

    for (; it1 != s1.end() && it2 != s2.end(); ++it1, ++it2)
    {
        assert(*it1 == *it2);
    }

    std::cout << "sets are equals" << std::endl;
}

void test_set()
{
    test_set_with_options<int64_t, 10000, t_std::greater<>, std::greater<>>();
    test_set_with_options<int64_t, 10000, t_std::greater_equal<>, std::greater_equal<>>();
    test_set_with_options<int64_t, 10000, t_std::less<>, std::less<>>();
    test_set_with_options<int64_t, 10000, t_std::less_equal<>, std::less_equal<>>();

    test_set_with_options<double, 100, t_std::greater<>, std::greater<>>();
    test_set_with_options<double, 100, t_std::greater_equal<>, std::greater_equal<>>();
    test_set_with_options<double, 100, t_std::less<>, std::less<>>();
    test_set_with_options<double, 100, t_std::less_equal<>, std::less_equal<>>();
}

int main()
{
    test_set();

    return 0;
}
