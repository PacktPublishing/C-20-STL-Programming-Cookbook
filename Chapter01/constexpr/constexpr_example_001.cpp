
#include <functional>
#include <cmath>
#include <array>
#include <list>
#include <queue>
#include <map>
#include <vector>
#include <iostream>

#include <string>
#include <algorithm>

#include <stdexcept>
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
void test_type_func_012()
{
	std::cout << "*** test 12  harmonic mean of two numbers at compile time ***" << std::endl;

	constexpr int a = 3;
	constexpr int b = 5;

	constexpr double hm = harmonic_mean(a, b);
	static_assert(hm == 3.75);

	std::cout << "Value computed at compile time: " << hm << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_type_func_013()
{
	std::cout << "*** test 13  harmonic mean of two numbers at run time ***" << std::endl;

	int a = 3;
	const int b = 5;

	const double hm = harmonic_mean(a, b);
	assert(hm == 3.75);

	std::cout << "Value computed at run time: " << hm << std::endl;
}

int main (int argc, char *argv[])
{
	
	std::cout << "test_main" << std::endl;

	test_type_func_012();
	test_type_func_013();


	return 0;
}
