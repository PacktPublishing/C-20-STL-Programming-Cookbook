#include <range/v3/all.hpp>
#include <iostream>

int main()
{
    auto range_int = ranges::view::ints(1, ranges::unreachable)
                | ranges::view::transform([](int i) {return i*i;})
                | ranges::view::take(10);

    for (int i : range_int)
        std::cout << i << ", ";
    std::cout << std::endl;

    const int sum = ranges::accumulate(range_int, 0);
    std::cout << "sum = " << sum;
    std::cout << std::endl;
 
    return 0;
}

