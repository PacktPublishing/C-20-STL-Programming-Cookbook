#include <vector>
#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T, typename U>
concept Same = std::is_same<T, U>::value;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename S, typename T>
 requires Same<T, typename S::value_type>
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
    bool found = in(v, std::string("two"));

    std::cout << "value was found in sequence: " <<
       std::boolalpha << found << std::endl;

    // this line do not compile
    //found = in(v, 1);

    return 0;
}

