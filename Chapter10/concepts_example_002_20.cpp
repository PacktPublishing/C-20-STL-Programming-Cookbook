#include <type_traits>

#include <string>
#include <set>
#include <vector>
#include <cassert>

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
template <typename T, typename U>
concept Equality_comparable_types = requires (T t, U u)
{
	{t == u} -> bool;
	{u == t} -> bool;
	{t != u} -> bool;
	{u != t} -> bool;
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
template <typename I>
concept Forward_iterator = requires (I i)
{
	typename value_type_t<I>;

	// It can be dereferenced
	{ *i } -> const value_type_t<I>&;

	// It can be incremented
	{ ++i } -> I&;        
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Forward_iterator I>
void advance (I& iter, int n)
{
    while (n != 0) {
        ++iter;
        n--;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Forward_iterator I>
int distance (I first, I limit)
{
    int n = 0;
    for(; first != limit; ++first, ++n) {
        ;
    }
    return n;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename I>
concept Bidirectional_iterator = 
	Forward_iterator<I> && requires (I i)
{
	 // It can be incremented
	{ --i } -> I&;        
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Bidirectional_iterator I>
void advance (I& iter, int n)
{
    if (n > 0)
        while (n != 0) { ++iter; --n; }
    if (n < 0)
        while (n != 0) { --iter; ++n; }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Forward_iterator I, typename T>
    requires Same<T, value_type_t<I>>
bool binary_search(I first, I limit, T const& value)
{
    if (first == limit)
        return false;

    auto mid = first;
    advance (mid, distance(first, limit) / 2);
    if (value < *mid)
        return binary_search(first, mid, value);
    else if (*mid < value)
        return binary_search(++mid, limit, value);
    else 
        return true;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
//-----------------------------------------------------------------------------
    int array[] = {1,2,4,5,6,7};
    const size_t len = sizeof(array) / sizeof(int);
    const int value = 5;
    bool bs_found = binary_search(array, array + len, value);
    std::cout << std::boolalpha <<
        "binary search found = " << bs_found << std::endl;
//-----------------------------------------------------------------------------    
    std::vector<int> vect = {1,2,4,5,6,7};
    bs_found = binary_search(vect.begin(), vect.end(), value);
    std::cout << std::boolalpha <<
        "binary search found = " << bs_found << std::endl;

//-----------------------------------------------------------------------------
    std::cout << 
        "type of the countainers is same = " <<
        std::is_same<
                    value_type_t<std::vector<int>>, 
                    value_type_t<int*>
                >::value << std::endl;

    return 0;
}

