#pragma once
#include <iostream>
#include <fstream>
#include <string>
#include "Movie.h"
#include "TVShow.h"
using namespace std;

class DataBase
{
private:
	Movie* movies;
	int num_of_movies;
	TVShow* tvshows;
	int num_of_tvshows;

	void readMoviesFromFile();
	void readTVShowsFromFile();

public:
	DataBase();
	DataBase(const DataBase& data);

	void writeMoviesToFile() const;
	void writeTVShowsToFile() const;

	void sortMovies();
	void sortTVShows();
	void addMovie(const Movie& movie);
	void addTVShow(const TVShow& tvshow);
	void deleteMovieByName(const string& name);
	void deleteTVShowByName(const string& name);
	Movie* findMovieByName(const string& name) const;
	TVShow* findTVShowByName(const string& name) const;
	Movie* findMoviesByCategory(const CATEGORY category, int* size) const;
	TVShow* findTVShowsByCategory(const CATEGORY category, int* size) const;
	void displayMovieList() const;
	void displayTVShowList() const;

	~DataBase();
};