#include <range/v3/all.hpp>
#include <iostream>

int main()
{
    std::vector<int> v{1,6,2,7,3,8};
    for (int i : v)
        std::cout << i << ", ";
    std::cout << std::endl;

    ranges::sort(v);
    for (int i : v)
        std::cout << i << ", ";
    std::cout << std::endl;

    auto rng = v | ranges::view::remove_if([](int i){return i % 2 == 1;})
                 | ranges::view::transform([](int i){return std::to_string(i);});
    for (std::string i : rng)
        std::cout << i << ", ";
    std::cout << std::endl;

    return 0;
}

