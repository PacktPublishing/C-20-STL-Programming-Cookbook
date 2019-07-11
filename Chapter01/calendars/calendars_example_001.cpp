

#include <date/date.h>

#include <chrono>
#include <iostream>
#include <cassert>


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_01()
{
	auto start = std::chrono::high_resolution_clock::now();

	[](int const count = 300000000) { for (int i = 0; i < count; ++i); }();

	auto diff = std::chrono::high_resolution_clock::now() - start;

	std::cout << std::chrono::duration<double, std::milli>(diff).count() <<
		"ms" << std::endl;

	std::cout << std::chrono::duration<double, std::nano>(diff).count() <<
		"ns" << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_02()
{
    using namespace date;

    date::year_month_day date_1 = 2019_y/July/9;
    date::year_month_day date_2 = 9_d/July/2019;
    assert(date_1 == date_2);


    std::cout << "test 01" << std::endl;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{

    test_calendars_01();
    test_calendars_02();


    return 0;
}

