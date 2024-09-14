#pragma once
#include "Item.h"

class Movie : public Item
{
private:
	int length;

	void setLength(int length);
	virtual void setProductionYear(int set_year);

public:
	Movie() : Item(), length(0) {}
	Movie(const string& name, int year, CATEGORY category, Date date, int length);
	Movie(const Movie& movie);
	Movie(const string& line);

	int getLength() const;
	virtual void display() const;

	virtual ~Movie() {}
};