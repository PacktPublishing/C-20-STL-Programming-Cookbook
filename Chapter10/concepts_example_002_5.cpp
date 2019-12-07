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

// The iterator_type of a class is a member type
template<typename T>
struct iterator_type
{
    using type = typename T::iterator;
};

template<typename T>
using iterator_type_t = typename iterator_type<T>::type;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// The value_type of a class is a member type
template<typename T>
struct value_type;

// The value_type of a class is a member type
template<typename T>
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
template <typename I>
concept Input_iterator = requires(I i)
{
	// Must have a value type
	typename value_type_t<I>;

	// It can be dereferenced
	{ *i } -> const value_type_t<I>&;

	// It can be incremented
	{ ++i } -> I&;
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

	{ range.begin() } -> iterator_type_t<R>;
	{ range.end() } -> iterator_type_t<R>;

	// The iterator type must be an input iterator
	requires Input_iterator<iterator_type_t<R>>;

	// The value of R is the same as it's
	// iterator value type
	requires Same< value_type_t<R>,
				   value_type_t<iterator_type_t<R>> >;
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Range R, Equality_comparable T>
  requires Same<T, value_type_t<R>>
bool in (R const& range, T const& value)
{
    for(auto const& x : range) {
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

    std::cout << "value was found: " << found << std::endl;

    return 0;
}
