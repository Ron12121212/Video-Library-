#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Movie.h"
#include "TVShow.h"
using namespace std;

class WatchList
{
private:
	Movie* movies;
	int num_of_movies = 0;
	TVShow* tvshows;
	int num_of_tvshows = 0;

	void readMoviesFromFile(const string& name);
	void readTVShowsFromFile(const string& name);
	void deleteListFromFile(const string& start) const;

public:
	WatchList() : movies(nullptr), tvshows(nullptr) {}
	WatchList(const string& name);
	WatchList(const WatchList& list);

	void writeMoviesToFile(const string& name) const;
	void writeTVShowsToFile(const string& name) const;

	void addMovieToWatchList(const Movie& movie);
	void addTVShowToWatchList(const TVShow& tvshow);
	void deleteMovieByNameFromWatchList(const string& name);
	void deleteTVShowByNameFromWatchList(const string& name);
	Movie* findMovieByName(const string& name) const;
	TVShow* findTVShowByName(const string& name) const;
	Movie* findMoviesByCategory(const CATEGORY category, int* size) const;
	TVShow* findTVShowsByCategory(const CATEGORY category, int* size) const;
	Movie topOfTheMovieList() const;
	TVShow topOfTheTVShowList() const;
	void displayMovieList() const;
	void displayTVShowList() const;
	void display() const;

	~WatchList();
};