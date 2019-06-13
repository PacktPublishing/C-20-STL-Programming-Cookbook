
#include <range/v3/all.hpp>

#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

int main()
{
    std::vector<int> v{1,6,2,7,3,8};

    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    ranges::sort(v);

    std::copy(v.begin(), v.end(),
        std::ostream_iterator<int>(std::cout, ", "));
    std::cout << std::endl;

    auto rng = v | ranges::view::remove_if([](int i){return i % 2 == 1;})
                 | ranges::view::transform([](int i){return std::to_string(i);});

    std::copy(rng.begin(), rng.end(),
        std::ostream_iterator<std::string>(std::cout, ", "));
    std::cout << std::endl;

    return 0;
}

