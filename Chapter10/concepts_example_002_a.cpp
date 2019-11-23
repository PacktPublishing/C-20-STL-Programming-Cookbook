#include <string>
#include <vector>

#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
concept bool Equality_comparable()
{
    return requires (T a, T b)
    {
        {a == b} -> bool;
        {a != b} -> bool;
    };   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename R>
concept bool Range()
{
    return requires (R range)
    {
        begin(range);
        end(range);
    };   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T, typename U>
concept bool Same()
{
    return std::is_same<T, U>::value;   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
struct value_type;

template<typename T>
struct value_type
{
    using type = typename T::value_type;
};

template<typename T>
using value_type_t = typename value_type<T>::type;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Range R, Equality_comparable T>
  requires Same<T, value_type_t<R>>()
bool in (R const& range, T const& value)
{
    for(Equality_comparable const& x : range)
    {
        if(x == value)
        {
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
    
    const bool found = in(v, value_one);

    std::cout << "value was found: " << found << std::endl;


    return 0;
}

