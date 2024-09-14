#include "Administrator.h"
#include "Menu.h"

Administrator::Administrator(const string& id, const string& first_name, const string& last_name, const string& password, Date date)
{
    try
    {
        setID(id);
        setFirstName(first_name);
        setLastName(last_name);
        setDateOfBirth(date);
        setPassword(password);
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
}

Administrator::Administrator(const Administrator& admin)
{
    try
    {
        setID(admin.getID());
        setFirstName(admin.getFirstName());
        setLastName(admin.getLastName());
        setDateOfBirth(admin.getDate());
        setPassword(admin.getPassword());
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
}

Administrator::Administrator(const string& line)
{
    string line_id, line_first_name, line_last_name, line_password, dob_str;
    int pos = 0;
    for (int i = 0; i < 4; i++)
    {
        int next_pos = line.find(',', pos);
        if (next_pos == string::npos)
            throw invalid_argument("Invalid Administrator format : " + line);
        switch (i)
        {
        case 0:
            line_id = line.substr(pos, next_pos - pos);
            break;
        case 1:
            line_first_name = line.substr(pos, next_pos - pos);
            break;
        case 2:
            line_last_name = line.substr(pos, next_pos - pos);
            break;
        case 3:
            line_password = line.substr(pos, next_pos - pos);
            break;
        }
        pos = next_pos + 1;
    }
    dob_str = line.substr(pos);
    try 
    { 
        setID(line_id);
        setFirstName(line_first_name);
        setLastName(line_last_name);
        setPassword(line_password);
        setDateOfBirth(Date(dob_str));
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
}

void Administrator::setPassword(const string& set_password)
{
    if (set_password == "")
        throw invalid_argument("Error ! invalid password, can not be empty");
    password = set_password;
}

const string& Administrator::getPassword() const
{
    return password;
}

bool Administrator::checkPassword(const string& str) const
{
    if (password == str)
        return true;
    return false;
}

Movie* Administrator::findMovie() const
{
    string name;
    cout << "Please enter the name of the movie : ";
    cin.ignore();
    getline(cin, name);
    return database.findMovieByName(name);
}

TVShow* Administrator::findTvshow() const
{
    string name;
    cout << "Please enter the name of the tv show : ";
    cin.ignore();
    getline(cin, name);
    return database.findTVShowByName(name);
}

Movie* Administrator::findMoviesByCategory(const CATEGORY category, int* size) const
{
    return database.findMoviesByCategory(category, size);
}

TVShow* Administrator::findTVShowsByCategory(const CATEGORY category, int* size) const
{
    return database.findTVShowsByCategory(category, size);
}

void Administrator::addNewMovie()
{
    string movie_name;
    int movie_year, movie_length;
    CATEGORY movie_category;
    cout << "Please enter movie name add : ";
    cin.ignore();
    getline(cin, movie_name);
    cout << endl << "Please choose the movie category :" << endl;
    movie_category = Menu::categoryMenu();
    cout << endl << "Please enter movie production year : ";
    cin >> movie_year;
    cout << endl << "Please enter movie length in minutes : ";
    cin >> movie_length;
    database.addMovie(Movie(movie_name, movie_year, movie_category, Date::getCurrentDate(), movie_length));
    database.sortMovies();
}

void Administrator::addNewTVShow()
{
    string tvshow_name;
    int tvshow_year, tvshow_seasons;
    CATEGORY tvshow_category;
    cout << "Please enter tv show name to add : ";
    cin.ignore();
    getline(cin, tvshow_name);
    cout << endl << "Please choose the tv show category :" << endl;
    tvshow_category = Menu::categoryMenu();
    cout << endl << "Please enter tv show production year : ";
    cin >> tvshow_year;
    cout << endl << "Please enter number of seasons : ";
    cin >> tvshow_seasons;
    database.addTVShow(TVShow(tvshow_name, tvshow_year, tvshow_category, Date::getCurrentDate(), tvshow_seasons));
    database.sortTVShows();
}

void Administrator::deleteMovie()
{
    string movie_name;
    cout << endl << "Please enter movie name to delete : ";
    cin.ignore();
    getline(cin, movie_name);
    Menu::clearScreen();
    database.deleteMovieByName(movie_name);
}

void Administrator::deleteTVShow()
{
    string tvshow_name;
    cout << endl << "Please enter tv show name to delete : ";
    cin.ignore();
    getline(cin, tvshow_name);
    Menu::clearScreen();
    database.deleteTVShowByName(tvshow_name);
}

void Administrator::displayMovieList() const
{
    database.displayMovieList();
}

void Administrator::displayTVShowList() const
{
    database.displayTVShowList();
}

void Administrator::writeToFile() const
{
    database.writeMoviesToFile();
    database.writeTVShowsToFile();
}