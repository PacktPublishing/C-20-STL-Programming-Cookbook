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
// The iterator_type of a class is a member type
template<typename T>
requires requires { typename T::iterator; }
struct iterator_type
{
    using type = typename T::iterator;
};

template<typename T>
using Iterator_type = typename iterator_type<T>::type;


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

// The value_type of an array is its element type.
template<typename T, int N>
struct value_type<T[N]>
{
    using type = T;
};

template<typename T>
using Value_type = typename value_type<T>::type;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename I>
concept bool Input_iterator()
{
    return requires(I i)
    {
        typename Value_type<I>;
        // It can be dereferenced
        { *i } -> const Value_type<I>&;
        // It can be incremented
        { ++i } -> I&;        
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
template <typename R>
concept bool Range()
{
    return requires (R range)
    {
	    // Must have a value type
        typename Value_type<R>;
	    // Must have an iterator type
	    typename Iterator_type<R>;

        { begin(range) } -> Iterator_type<R>;
        { end(range) } -> Iterator_type<R>;
        
        // The iterator type must be an input iterator
        requires Input_iterator<Iterator_type<R>>();

        // The value of R is the same as it's
        // iterator value type
        requires Same< Value_type<R>,
                       Value_type<Iterator_type<R>>>();
    };   
}

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

