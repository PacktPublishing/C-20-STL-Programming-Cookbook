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
    const std::string value_one("one");
    const std::string value_two("two");
    const std::string value_three("three");

    std::vector<std::string> v {value_one, value_two, value_three};
    bool found = in(v, value_one);
    std::cout << "value was found in sequence: " <<
        std::boolalpha << found << std::endl;

    // this line do not compile
    //found = in(v, 1);

    return 0;
}

