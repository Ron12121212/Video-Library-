#include "Item.h"

void Item::setName(const string& set_name)
{
	if (set_name == "")
		throw invalid_argument("Error ! invalid movie name, can not be empty");
	for (char c : set_name)
	{
		if ((c < 'A' || (c > 'Z' && c < 'a') || c > 'z') && c != ' ')
			throw invalid_argument("Error ! invalid movie name, can only contain characters");
	}
	name = set_name;
}

void Item::setCategory(const CATEGORY set_category)
{
	category = set_category;
}

void Item::setEnteredIntoSystemDate(const Date set_date)
{
	entered_into_system = set_date;
}

const string& Item::getName() const
{ 
	return name; 
}

Date Item::getEnteredIntoSystemDate() const
{
	return entered_into_system;
}

int Item::getProductionYear() const
{
	return production_year;
}

CATEGORY Item::getCategory() const
{
    return category;
}

string Item::toLowerCase(const string& str)
{
	string result = str;
	for (char& c : result)
	{
		c = tolower(c); // Convert char to lowercase
	}
	return result;
}