#include <vector>
#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename S, typename T>
bool in (S const& seq, T const& value)
{
    for(auto const& x : seq) {
        if(x == value) {
            return true;
        }
    }
    return false;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    std::vector<std::string> v{"one", "two", "three"};
    bool found = in(v, "two");

    std::cout << "value was found in sequence: " <<
       std::boolalpha << found << std::endl;

    // this line do not compile
    //found = in(v, 1);

    return 0;
}

