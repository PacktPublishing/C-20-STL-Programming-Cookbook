#include <string>
#include <algorithm>
#include <iostream>

int main()
{
    std::vector<int> v{1,6,2,7,3,8};
    for (int i : v)
        std::cout << i << ", ";
    std::cout << std::endl;

    std::sort(v.begin(), v.end());
    for (int i : v)
        std::cout << i << ", ";
    std::cout << std::endl;
 
    std::vector<int> vi;
    std::copy_if(v.begin(), v.end(), 
        std::back_inserter(vi), [](int i){return i % 2 != 1;});

    std::vector<std::string> vs;
    std::transform(vi.begin(), vi.end(), 
        std::back_inserter(vs), [](int i){return std::to_string(i);});

    for (std::string i : vs)
        std::cout << i << ", ";
    std::cout << std::endl;

    return 0;
}

