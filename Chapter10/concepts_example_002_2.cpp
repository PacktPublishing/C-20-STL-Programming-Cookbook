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
// The value_type of a class is a member type
template<typename T>
requires requires { typename T::value_type; }
struct value_type
{
    using type = typename T::value_type;
};

// The value_type of a pointer is the type of element pointed to.
template<typename T>
struct value_type<T*>
{
    using type = T;
};

// The value_type of an arry is its element type.
template<typename T, int N>
struct value_type<T[N]>
{
    using type = T;
};

template<typename T>
using Value_type = typename value_type<T>::type;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Range R, Equality_comparable T>
  requires Same<T, Value_type<R>>()
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

