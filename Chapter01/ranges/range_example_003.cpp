
#include <range/v3/all.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    auto range_int = ranges::view::ints(5, ranges::unreachable)
                | ranges::view::transform([](int i) {return 2*i;})
                | ranges::view::take(100);

    auto i = std::begin(range_int);
    std::cout << *(++i) << std::endl;
    
    return 0;
}

