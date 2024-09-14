#include "Date.h"

Date::Date(int day, int month, int year)
{
    try { checkDate(day, month, year); }
    catch (const invalid_argument& e)
    {
        throw;
    }
    this->day = day;
    this->month = month;
    this->year = year;
}

Date::Date(const string& str)
{
    int str_day = 0, str_month = 0, str_year = 0;
    int firstSlash = str.find('/');
    int secondSlash = str.find('/', firstSlash + 1);
    if (firstSlash != string::npos && secondSlash != string::npos)
    {
        str_day = stoi(str.substr(0, firstSlash));
        str_month = stoi(str.substr(firstSlash + 1, secondSlash - firstSlash - 1));
        str_year = stoi(str.substr(secondSlash + 1));
    }
    else
        throw invalid_argument("Invalid date format in file");
    try { checkDate(str_day, str_month, str_year); }
    catch (const invalid_argument& e)
    {
        throw;
    }
    day = str_day;
    month = str_month;
    year = str_year;
}

bool Date::checkDate(int day, int month, int year)
{
    if (year < 1)
        throw invalid_argument("Invalid year value");
    int daysInMonth[] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
    if (year % 4 == 0) // Leap year
        daysInMonth[1] = 29;
    if (month < 1 || month > 12)
        throw invalid_argument("Invalid month value");
    if (day < 1 || day > daysInMonth[month - 1])
        throw invalid_argument("Invalid day value");
    return true;
}

int Date::getDay() const
{
    return day;
}

int Date::getMonth() const
{
    return month;
}

int Date::getYear() const
{
    return year;
}

Date Date::getCurrentDate()
{
    time_t now = time(nullptr);
    tm* ltm = localtime(&now);
    return Date(ltm->tm_mday, ltm->tm_mon + 1, ltm->tm_year + 1900);
}

void Date::displayDate() const
{
    cout << day << "/" << month << "/" << year;
}