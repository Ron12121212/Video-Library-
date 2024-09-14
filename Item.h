#pragma once
#include <string>
#include <iostream>
#include "Genre.h"
#include "Date.h"
using namespace std;

class Item
{
protected:
	string name;
	int production_year;
	CATEGORY category;
    Date entered_into_system;

	void setName(const string& set_name);
	virtual void setProductionYear(int set_year) = 0;
	void setCategory(const CATEGORY set_category);
	void setEnteredIntoSystemDate(const Date set_date);

public:
	const string& getName() const; 
	int getProductionYear() const; 
	CATEGORY getCategory() const;
    Date getEnteredIntoSystemDate() const;
	static string toLowerCase(const string& str);
	virtual void display() const = 0;

	virtual ~Item() {}
};