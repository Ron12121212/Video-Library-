#pragma once
#include "Item.h"

class TVShow : public Item
{
private:
	int seasons;
	int* episodes;

	void setSeasons(int set_seasons);
	void setEpisodes();
	virtual void setProductionYear(int set_year);

public:
	TVShow() : Item(), seasons(0), episodes(nullptr) {}
	TVShow(const string& name, int year, CATEGORY category, Date date, int seasons);
	TVShow(const string& name, int year, CATEGORY category, Date date, int seasons, int* episodes);
	TVShow(const TVShow& tvshow);
	TVShow(const string& line);

	int getSeasons() const;
	int* getEpisodes() const;
    virtual void display() const;

	virtual ~TVShow() {}
};