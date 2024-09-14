#pragma once
#include "Account.h"
#include "DataBase.h"

class Administrator : public Account
{
private:
	DataBase database;
	string password;

	void setPassword(const string& set_password);	

public:
	Administrator() : Account(), database(), password("") {}
	Administrator(const string& id, const string& first_name, const string& last_name, const string& password, Date date);
	Administrator(const Administrator& admin);
	Administrator(const string& line);

	const string& getPassword() const;
	bool checkPassword(const string& str) const;
	virtual Movie* findMovie() const;
	virtual TVShow* findTvshow() const;
	virtual Movie* findMoviesByCategory(const CATEGORY category, int* size) const;
	virtual TVShow* findTVShowsByCategory(const CATEGORY category, int* size) const;
	void addNewMovie();
	void addNewTVShow();
	virtual void deleteMovie();
	virtual void deleteTVShow();
	void displayMovieList() const;
	void displayTVShowList() const;
	virtual void writeToFile() const;

	virtual ~Administrator() {}
};