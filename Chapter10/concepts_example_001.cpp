#include <string>
#include <vector>

#include <iostream>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
concept bool Equality_Comparable = requires(T a, T b)
{
    {a == b} -> bool;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
concept bool Stringable = requires(T a)
{
    // T implements the to_string method
    {a.to_string()} -> std::string;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
concept bool Has_String_Func = requires(T a)
{
    // for T exists a to_string function, 
    // taking T as parameter and returning a std::string
    {to_string(a)} -> std::string;
};

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
struct Person
{
    double height;
    int weight;

    Person(double a, int b)
        : height(a), weight(b)  
    {}

    std::string to_string()
    {
        return "Height: " + std::to_string(height) +
            " Weight: " + std::to_string(weight);
    }

};


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void prity_print(Stringable a)
{
    std::cout << a.to_string() << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template <typename T>
concept bool Integral()
{
    return std::is_integral<T>::value;   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<Integral T>
T gcd(T a, T b)
{
    if(b == 0)
    {
       return a;
    }
    else
    {
        return gcd(b, a % b);
    }
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    Person jonathan(5.7, 130);
    prity_print(jonathan);

    std::cout << "gcd of 18 and 30 is: " << gcd(18,30) << std::endl;

    return 0;
}

