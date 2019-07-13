#include <date/date.h>

#include <chrono>
#include <iostream>
#include <cassert>

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_01()
{
    using namespace date;

    std::cout << "*** test 01 ***" << std::endl;
    // full-calendar-type
    date::year_month_day date_1 = 2019_y/July/9;
    date::year_month_day date_2 = 9_d/July/2019;
    assert(date_1 == date_2);

    std::cout << "year month day: " << date_1 << std::endl;   
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_02()
{
    using namespace date;

    std::cout << "*** test 02 ***" << std::endl;
    // field type year
    date::year y = date::year{2019};
    std::cout << "year: " << y << std::endl;

    // create a full-calendar-type from 
    // three different field types: day, month and year
    date::year_month_day date_1 = {date::year{2019},date::month{7},date::day{13}};
    std::cout << "year month day: " << date_1 << std::endl;
  
    constexpr date::year_month_day date_2 = {date::year{2019},date::month{7},date::day{21}};
    std::cout << "year month day: " << date_2 << std::endl;
 
    constexpr date::year_month_day date_3 = 2019_y/July/21;
    std::cout << "year month day: " << date_3 << std::endl;

    static_assert(date_2 == date_3);

    static_assert(date_2.year() == 2019_y);
    static_assert(date_2.month() == July);
    static_assert(date_2.day() == 21_d);
}


    using days_ = std::chrono::duration<int32_t, std::ratio<86400>>;
    template <class Duration> using sys_time_ = std::chrono::time_point<std::chrono::system_clock, Duration>;


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_03()
{
    using namespace std::chrono;
    using namespace date;

    std::cout << "*** test 03 ***" << std::endl;
    
    auto d = std::chrono::system_clock::now();
    std::cout << "day: " << d << std::endl;

    auto dr = std::chrono::floor<date::days>(d);
    std::cout << "day rounded: " << dr << std::endl;


    using sys_days_ = sys_time_<days_>;
    std::chrono::system_clock::time_point tp = sys_days_{2019_y/July/13};
    std::cout << "time point: " << tp << std::endl;    


}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    test_calendars_01();
    test_calendars_02();
    test_calendars_03();

    return 0;
}

