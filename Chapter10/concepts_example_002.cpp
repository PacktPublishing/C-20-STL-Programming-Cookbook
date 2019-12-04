#include <string>
#include <vector>

#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
concept Equality_comparable = requires (T a, T b)
{
    {a == b} -> bool;
    {a != b} -> bool;
};



//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename R>
concept bool Range = requires (R range)
{
    begin(range);
    end(range);
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T, typename U>
concept bool Same = std::is_same<T, U>::value;


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
template<typename R, typename T>
  requires Range<R> &&
           Equality_comparable<T> &&
           Same<value_type_t<R>, T>
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
    std::vector<std::string> v {"one", "two", "three"};
    
    const bool found = in(v, std::string("two"));
    std::cout << "value was found: " << found << std::endl;

    return 0;
}

