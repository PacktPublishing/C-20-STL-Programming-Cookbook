#include <string>
#include <map>
#include <vector>

#include <stdexcept>
#include <iostream>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
concept bool like_map = 
    requires (T t) { 
        typename T::value_type;
        typename T::value_type::first_type;
        typename T::value_type::second_type;

    t[typename T::value_type::first_type{}];

    };

void test(like_map m)
{
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    test(std::map<int,int>{});
    test(std::vector<std::pair<int,int>>{});

    std::cout << "program end" << std::endl;
    return 0;
}

