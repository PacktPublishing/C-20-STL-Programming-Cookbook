
#include <string>
#include <iostream>
#include <cassert>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
constexpr double harmonic_mean(int a, int b)
{
    double ret_val = 0.0;
    ret_val = 2.0 * a * b / (a + b);

    return ret_val;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void harmonic_mean_compile_time()
{
    std::cout << "*** harmonic mean of two numbers at compile time ***" << std::endl;

    const int a = 3;
    constexpr int b = 5;

    constexpr double hm = harmonic_mean(a, b);
    static_assert(hm == 3.75);

    std::cout << "Value computed at compile time: " << hm << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void harmonic_mean_run_time()
{
    std::cout << "*** harmonic mean of two numbers at run time ***" << std::endl;

    int a = 3;
    const int b = 5;

    const double hm = harmonic_mean(a, b);
    assert(hm == 3.75);

    std::cout << "Value computed at run time: " << hm << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main (int argc, char *argv[])
{

    harmonic_mean_compile_time();
    harmonic_mean_run_time();

    return 0;
}

