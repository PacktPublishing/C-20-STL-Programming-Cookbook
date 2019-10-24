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
template <typename T, typename U>
concept bool Equality_comparable()
{
    return requires (T t, U u)
    {
        {t == u} -> bool;
        {u == t} -> bool;        
        {t != u} -> bool;
        {u != t} -> bool;        
    };   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T, typename U>
concept bool Same_as()
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

// The value_type of an array is its element type.
template<typename T, int N>
struct value_type<T[N]>
{
    using type = T;
};

template<typename T>
using value_type_t = typename value_type<T>::type;

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
using iterator_t = typename iterator_type<T>::type;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename I>
concept bool Input_iterator()
{
    return requires(I i)
    {
  	    // Must have a value type
        typename value_type_t<I>;

        // It can be dereferenced
        { *i } -> const value_type_t<I>&;

        // It can be incremented
        { ++i } -> I&;        
    };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename R>
concept bool Range()
{
    return requires (R range)
    {
	    // Must have a value type
        typename value_type_t<R>;
	    // Must have an iterator type
	    typename iterator_t<R>;

        { begin(range) } -> iterator_t<R>;
        { end(range) } -> iterator_t<R>;
        
        // The iterator type must be an input iterator
        requires Input_iterator<iterator_t<R>>();

        // The value of R is the same as it's
        // iterator value type
        requires Same_as< value_type_t<R>,
                       value_type_t<iterator_t<R>>>();
    };   
}

template <typename S>
concept bool Sequence()
{
    return Range<S>() && requires (S seq)
    {
        { seq.front() } -> const value_type_t<S>&;
        { seq.back() } -> const value_type_t<S>&;
    };
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Sequence S, Equality_comparable T>
  requires Same_as<T, value_type_t<S>>()
bool in (S const& seq, T const& value)
{
    for(auto const& x : seq)
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

