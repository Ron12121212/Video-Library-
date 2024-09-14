#include "User.h"
#include "Menu.h"

User::User(const string& id, const string& first_name, const string& last_name, Date date)
{
    try
    {
        setID(id);
        setFirstName(first_name);
        setLastName(last_name);
        setDateOfBirth(date);
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
    watch_list = WatchList(first_name);
}

User::User(const User& user)
{
    try
    {
        setID(user.getID());
        setFirstName(user.getFirstName());
        setLastName(user.getLastName());
        setDateOfBirth(user.getDate());
        watch_list = user.watch_list;
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
}

User::User(const string& line)
{
    string line_id, line_first_name, line_last_name, dob_str;
    int pos = 0;
    for (int i = 0; i < 3; i++)
    {
        int next_pos = line.find(',', pos);
        if (next_pos == string::npos)
            throw invalid_argument("Invalid User format : " + line);
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
        }
        pos = next_pos + 1;
    }
    dob_str = line.substr(pos);
    try 
    { 
        setID(line_id);
        setFirstName(line_first_name);
        setLastName(line_last_name);
        setDateOfBirth(Date(dob_str));
        watch_list = WatchList(line_first_name);
    }
    catch (const invalid_argument& e)
    {
        throw;
    }
}

Movie* User::findMovie() const
{
    string name;
    cout << "Please enter the name of the movie : ";
    cin.ignore();
    getline(cin, name);
    return watch_list.findMovieByName(name);
}

Movie* User::findMovie(const string& name) const
{
    return watch_list.findMovieByName(name);
}

TVShow* User::findTvshow() const
{
    string name;
    cout << "Please enter the name of the tv show : ";
    cin.ignore();
    getline(cin, name);
    return watch_list.findTVShowByName(name);
}

TVShow* User::findTVShow(const string& name) const
{
    return watch_list.findTVShowByName(name);
}

Movie* User::findMoviesByCategory(const CATEGORY category, int* size) const
{
    Movie* by_category = watch_list.findMoviesByCategory(category, size);
    if (by_category == nullptr)
        throw invalid_argument("Your watch list has no movies by category: " + Genre::categoryToString(category) + "\n");
    return by_category;
}

TVShow* User::findTVShowsByCategory(const CATEGORY category, int* size) const
{
    TVShow* by_category = watch_list.findTVShowsByCategory(category, size);
    if (by_category == nullptr)
        throw invalid_argument("Your watch list has no tv shows by category: " + Genre::categoryToString(category) + "\n");
    return by_category;
    
}

void User::addNewMovie(const Movie& movie)
{
    watch_list.addMovieToWatchList(movie);
}

void User::addNewTVShow(const TVShow& tvshow)
{
    watch_list.addTVShowToWatchList(tvshow);
}

void User::watchMovie() 
{
    Movie movie = watch_list.topOfTheMovieList();
    movie.display();
    cout << endl << "Would you like to delete this movie from your watch list ?" << endl;
    int choice = Menu::yesOrNo();
    if (choice == 1)   // delete movie
        watch_list.deleteMovieByNameFromWatchList(movie.getName());
}

void User::watchTVShow()
{
    TVShow tvshow = watch_list.topOfTheTVShowList();
    tvshow.display();
    cout << endl << "Would you like to delete this tv show from your watch list ?" << endl;
    int choice = Menu::yesOrNo();
    if (choice == 1)   // delete tv show
        watch_list.deleteTVShowByNameFromWatchList(tvshow.getName());
}

void User::deleteMovie()
{
    string movie_name;
    cout << endl << "Please enter movie name to delete : ";
    cin >> movie_name;
    Menu::clearScreen();
    watch_list.deleteMovieByNameFromWatchList(movie_name);
}

void User::deleteTVShow()
{
    string tvshow_name;
    cout << endl << "Please enter tv show name to delete : ";
    cin >> tvshow_name;
    Menu::clearScreen();
    watch_list.deleteTVShowByNameFromWatchList(tvshow_name);
}

void User::displayMovieWatchlist() const
{
    watch_list.displayMovieList();
}

void User::displayTVShowWatchlist() const
{
    watch_list.displayTVShowList();
}

void User::writeToFile() const
{
    watch_list.writeMoviesToFile(first_name);
    watch_list.writeTVShowsToFile(first_name);
}