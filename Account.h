#pragma once
#include "Date.h"
#include <string>
#include <iostream>
#include "Movie.h"
#include "TVShow.h"
using namespace std;

class Account
{
protected:
    string id;
    string first_name;
    string last_name;
    Date date_of_birth;

    void setID(const string& set_id);
    void setFirstName(const string& set_first_name);
    void setLastName(const string& set_last_name);
    void setDateOfBirth(Date set_date);

public:
    const string& getID() const;
    const string& getFirstName() const;
    const string& getLastName() const;
    Date getDate() const;
    virtual Movie* findMovie() const = 0;
    virtual TVShow* findTvshow() const = 0;
    virtual Movie* findMoviesByCategory(const CATEGORY category, int* size) const = 0;
    virtual TVShow* findTVShowsByCategory(const CATEGORY category, int* size) const = 0;
    virtual void deleteMovie() = 0;
    virtual void deleteTVShow() = 0;
    void display() const;
    virtual void writeToFile() const = 0;

    virtual ~Account() {}
};