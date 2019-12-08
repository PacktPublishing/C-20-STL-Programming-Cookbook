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
template <typename T, typename U>
concept Same = std::is_same<T, U>::value;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
struct iterator_type;

template<typename T>
using iterator_type_t = typename iterator_type<T>::type;

// The iterator_type of a class is a member type
template<typename T>
requires requires {typename T::iterator;}
struct iterator_type<T>
{
    using type = typename T::iterator;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// The value_type of a class is a member type
template<typename T>
struct value_type;

template<typename T>
using value_type_t = typename value_type<T>::type;


// The value_type of a class is a member type
template<typename T>
requires requires {typename T::value_type;}
struct value_type<T>
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


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename R>
concept Range = requires (R range)
{
	// Must have a value type
	typename value_type_t<R>;
	// Must have an iterator type
	typename iterator_type_t<R>;

	{range.begin()} -> iterator_type_t<R>;
	{range.end()} -> iterator_type_t<R>;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Range R, Equality_comparable T>
  requires Same<value_type_t<R>, T>
bool in (R const& range, T const& value)
{
    for(const auto& x : range) {
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
    std::vector<std::string> v {"one", "two", "three"};
    
    const bool found = in(v, std::string("two"));
    std::cout << "value was found: " << found << std::endl;

    return 0;
}
