
#include <range/v3/all.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    for (int i : ranges::view::ints(1, ranges::unreachable)
                | ranges::view::transform([](int i) {return i*i;})
                | ranges::view::take(10))
        std::cout << i << ", ";
    std::cout << std::endl;

    const int sum = ranges::accumulate(
        ranges::view::ints(1, ranges::unreachable)
                | ranges::view::transform([](int i) {return i*i;})
                | ranges::view::take(10)
        ,0);

    std::cout << "sum = " << sum;
    std::cout << std::endl;
 
    return 0;
}

