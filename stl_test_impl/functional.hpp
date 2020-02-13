//
// Created by Сергей Бородин on 13.02.2020.
//

#ifndef STL_TEST_SAMPLE_FUNCTIONAL_HPP
#define STL_TEST_SAMPLE_FUNCTIONAL_HPP

namespace t_std
{

template<typename T = void>
struct greater
{
    inline bool operator()(T const & lft, T const & rht)
    {
        return rht < lft;
    }
};

template<>
struct greater<void>
{
    template<typename T1, typename T2>
    inline bool operator()(T1&& lft, T2&& rht)
    {
        return rht < lft;
    }
};

template<typename T = void>
struct greater_equal
{
    inline bool operator()(T const & lft, T const & rht)
    {
        return rht < lft || !(lft < rht);
    }
};

template<>
struct greater_equal<void>
{
    template<typename T1, typename T2>
    inline bool operator()(T1&& lft, T2&& rht)
    {
        return rht < lft || !(lft < rht);
    }
};

template<typename T = void>
struct less
{
    inline bool operator()(T const & lft, T const & rht)
    {
        return lft < rht;
    }
};

template<>
struct less<void>
{
    template<typename T1, typename T2>
    inline bool operator()(T1&& lft, T2&& rht)
    {
        return lft < rht;
    }
};

template<typename T = void>
struct less_equal
{
    inline bool operator()(T const & lft, T const & rht)
    {
        return lft < rht || !(rht < lft);
    }
};

template<>
struct less_equal<void>
{
    template<typename T1, typename T2>
    inline bool operator()(T1&& lft, T2&& rht)
    {
        return lft < rht || !(rht < lft);
    }
};

}

#endif //STL_TEST_SAMPLE_FUNCTIONAL_HPP
