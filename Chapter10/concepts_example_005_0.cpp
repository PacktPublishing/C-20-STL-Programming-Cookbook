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
        int(); 
    };


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{

    static_assert(like_map<std::map<int,int>>);
    static_assert(like_map<std::vector<int>>);

    std::cout << "program end" << std::endl;
    return 0;
}

