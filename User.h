#pragma once
#include "Account.h"
#include "WatchList.h"

class User : public Account
{
private:
	WatchList watch_list;

public:
	User() : Account() {}
	User(const string& id, const string& first_name, const string& last_name, Date date);
	User(const User& user);
	User(const string& line);

	virtual Movie* findMovie() const;
	Movie* findMovie(const string& name) const;
	virtual TVShow* findTvshow() const;
	TVShow* findTVShow(const string& name) const;
	virtual Movie* findMoviesByCategory(const CATEGORY category, int* size) const;
	virtual TVShow* findTVShowsByCategory(const CATEGORY category, int* size) const;
	void addNewMovie(const Movie& movie);
	void addNewTVShow(const TVShow& tvshow);
	void watchMovie();
	void watchTVShow();
	virtual void deleteMovie();
	virtual void deleteTVShow();
	void displayMovieWatchlist() const;
	void displayTVShowWatchlist() const;
	virtual void writeToFile() const;

	virtual ~User() {}
};