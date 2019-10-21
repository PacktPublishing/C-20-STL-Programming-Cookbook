#include <string>
#include <vector>

#include <stdexcept>
#include <iostream>


struct Bar {void foo() {} }; 
struct Baz {void foo() {} }; 


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
template<typename T>
concept bool has_foo = 
    requires (T t) { 
        t.foo(); 
    };


void defrangulate(has_foo f1, has_foo f2)
{
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    Bar bar{};
    Baz baz{};
    defrangulate(bar, bar);

    std::cout << "program end" << std::endl;
    return 0;
}

