#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <string>
using namespace std;

class Date
{
private:
	int day;
	int month;
	int year;

public:
	Date() : day(0), month(0), year(0) {}
	Date(int day, int month, int year);
	Date(const string& str);

	bool checkDate(int day, int month, int year);
	int getDay() const;
	int getMonth() const;
	int getYear() const;
	static Date getCurrentDate();
	void displayDate() const;
};

static bool operator>(const Date& date1, const Date& date2)
{
	if (date1.getYear() > date2.getYear())
		return true;
	if (date1.getYear() < date2.getYear())
		return false;
	if (date1.getMonth() > date2.getMonth())
		return true;
	if (date1.getMonth() < date2.getMonth())
		return false;
	return date1.getDay() > date2.getDay();
}