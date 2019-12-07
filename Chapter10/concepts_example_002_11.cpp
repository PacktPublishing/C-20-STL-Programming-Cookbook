#include <string>
#include <set>
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
template<typename T>
struct key_type;

// The key_type of a class is a member type
template<typename T>
struct key_type
{
    using type = typename T::key_type;
};

template<typename T>
using key_type_t = typename key_type<T>::type;


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
template <typename S>
concept Sequence = Range<S>() && requires (S seq)
{
	{ seq.front() } -> const value_type_t<S>&;
	{ seq.back() } -> const value_type_t<S>&;
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename A>
concept Associative_container = Range<A> &&
requires
{
	typename key_type_t<A>;
} &&
requires (A assoc_c, key_type_t<A> k)
{
	{ assoc_c.empty() } -> bool;
	{ assoc_c.size() } -> int;
	{ assoc_c.find(k) } -> iterator_type_t<A>;
	{ assoc_c.count(k) } -> int;
	{ assoc_c.end() } -> iterator_type_t<A>;
};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Sequence S, Equality_comparable T>
    requires Same<T, value_type_t<S>>
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
template<Associative_container A, typename K>
    requires Same<K, key_type_t<A>>
bool in (A const& assoc, K const& key)
{
    return assoc.find(key) != assoc.end();
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    std::vector<std::string> v {"one", "two", "three"};
    const bool found = in(v, std::string("two"));
    std::cout << "value was found: " << found << std::endl;

    std::set<std::string> s {"one", "two", "three"};
    const bool found_assoc = in(s, std::string("two"));
    std::cout << "value was found in assoc container: " << found_assoc << std::endl;

    return 0;
}

