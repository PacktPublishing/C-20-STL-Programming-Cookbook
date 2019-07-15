#include <date/date.h>
#include <date/tz.h>

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

    // extract the year from a full-calendar-type
    static_assert(date_2.year() == 2019_y);
    static_assert(date_2.month() == July);
    static_assert(date_2.day() == 21_d);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_03()
{
    using namespace date;

    std::cout << "*** test 03 ***" << std::endl;

    // get day and time now, as a time-point
    auto day_time_now = std::chrono::system_clock::now();
    std::cout << "day: " << day_time_now << std::endl;

    // rount this time-point to days
    auto day_time_now_round = std::chrono::floor<date::days>(day_time_now);
    std::cout << "day rounded: " << day_time_now_round << std::endl;

    // create a year_month_day from the rouded time-point
    date::year_month_day date_1{day_time_now_round};
    std::cout << "year month day from time-point: " << date_1 << std::endl;

}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_04()
{
    using namespace std::chrono;
    using namespace date;
    std::cout << "*** test 05 ***" << std::endl;

    // create a time-point using a date
    std::chrono::system_clock::time_point day_1 = date::sys_days{2019_y/July/13};
    std::cout << "time-point from year month day: " << day_1 << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
// define a duration with coarse precision: 24 hours.
using days_ = std::chrono::duration<int32_t, std::ratio<86400>>;

template <class Duration>
using sys_time_ = std::chrono::time_point<std::chrono::system_clock, Duration>;

// define a time-point using system-clock and a coarse duration.
using sys_days_ = sys_time_<days_>;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_04a()
{
    using namespace std::chrono;
    using namespace date;
    std::cout << "*** test 04a ***" << std::endl;

    // create a time-point using a date
    std::chrono::system_clock::time_point day_1 = sys_days_{2019_y/July/13};
    std::cout << "day as time point: " << day_1 << std::endl;
}


//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_05()
{
    using namespace std::chrono;
    using namespace date;
    std::cout << "*** test 05 ***" << std::endl;

    // create today as a year_month_day from a time-point rouded to a day
    date::year_month_day today =
        std::chrono::floor<date::days>(std::chrono::system_clock::now());
    std::cout << "year:  " << today.year() << std::endl;
    std::cout << "month february:  " << date::month(2) << std::endl;
    std::cout << "february last day:  " << date::month_day_last(date::month(2)) << std::endl;

    // create a last february day as a year_month_day from today
    date::year_month_day last_day_february{
        today.year(),
        date::month(2),
        //date::day{date::month_day_last(date::month(2))}
        date::day{21}
    };
    std::cout << "february last day: " << last_day_february << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void test_calendars_06()
{
    using namespace std::chrono;
    using namespace date;
    std::cout << "*** test 06 ***" << std::endl;

    std::chrono::system_clock::time_point day_time_now =
        std::chrono::floor<std::chrono::milliseconds>(std::chrono::system_clock::now());

    std::cout << "day time now: " << day_time_now << std::endl;

    auto tp = date::sys_days{2019_y/7/13} + 5h + 15min + 9s;
    std::cout << "a time point: " << tp << std::endl;

    auto local_tp =
        date::zoned_time{date::current_zone(), std::chrono::system_clock::now()};
    std::cout << "a local time point : " << local_tp  << std::endl;

    std::cout << date::zoned_time{date::current_zone(),
        std::chrono::system_clock::now()}  << std::endl;
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
int main()
{
    test_calendars_01();
    test_calendars_02();
    test_calendars_03();
    test_calendars_04();
    test_calendars_04a();
    test_calendars_05();
    test_calendars_06();

    return 0;
}

