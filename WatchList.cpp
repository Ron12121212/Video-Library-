#include "WatchList.h"

WatchList::WatchList(const string& name)
{
    readMoviesFromFile(name);
    readTVShowsFromFile(name);
}

WatchList::WatchList(const WatchList& list)
{
    num_of_movies = list.num_of_movies;
    movies = new Movie[num_of_movies];
    for (int i = 0; i < num_of_movies; i++)
    {
        movies[i] = list.movies[i];
    }
    num_of_tvshows = list.num_of_tvshows;
    tvshows = new TVShow[num_of_tvshows];
    for (int i = 0; i < num_of_tvshows; i++)
    {
        tvshows[i] = list.tvshows[i];
    }
}

void WatchList::readMoviesFromFile(const string& name)
{
    ifstream watch_lists_file("watch lists.txt");
    if (!watch_lists_file.is_open())
        throw invalid_argument("Failed to open file watch lists.txt");
    int count = 0;
    string line;
    while (getline(watch_lists_file, line)) // Find the user's watch list
    {
        if (line.find(name) != string::npos)
            break;
    }
    while (getline(watch_lists_file, line) && line.find('%') == string::npos) // Count amount of movies in user's list
    {
        count++;
    }
    watch_lists_file.clear();
    watch_lists_file.seekg(0, ios::beg);
    while (getline(watch_lists_file, line)) // Find the user's watch list
    {
        if (line.find(name) != string::npos)
            break;
    }
    num_of_movies = count;
    movies = new Movie[num_of_movies];
    
    if (num_of_movies != 0)
    {
        int index = 0;
        while (getline(watch_lists_file, line) && line != "%")  // Read movies data from the user's watch list
        {
            try
            { movies[index] = Movie(line); }
            catch (const invalid_argument& e)
            {
                throw;
            }
            index++;
        }
    }
    watch_lists_file.close();
}

void WatchList::readTVShowsFromFile(const string& name)
{
    ifstream watch_lists_file("watch lists.txt");
    if (!watch_lists_file.is_open())
        throw invalid_argument("Failed to open file watch lists.txt");

    int count = 0;
    string line;
    while (getline(watch_lists_file, line)) // Find the user's watch list
    {
        if (line.find(name) != string::npos)
            break;
    }
    while (getline(watch_lists_file, line)) // Skip movies data
    {
        if (line.find('%') != string::npos)
            break;
    }
    while (getline(watch_lists_file, line) && line.find(":") == string::npos) // Count amount of tvshows in user's list
    {
        count++;
    }
    num_of_tvshows = count;
    tvshows = new TVShow[num_of_tvshows];

    watch_lists_file.clear();
    watch_lists_file.seekg(0, ios::beg);
    while (getline(watch_lists_file, line)) // Find the user's watch list
    {
        if (line.find(name) != string::npos)
            break;
    }
    while (getline(watch_lists_file, line)) // Skip all admins data
    {
        if (line.find('%') != string::npos)
            break;
    }
    if (num_of_tvshows != 0)
    {
        int index = 0;
        while (getline(watch_lists_file, line) && line.find(":") == string::npos)
        {
            try
            { tvshows[index] = TVShow(line); }
            catch (const invalid_argument& e)
            {
                throw;
            }
            index++;
        }
    }
    watch_lists_file.close();
}

void WatchList::writeMoviesToFile(const string& name) const
{
    deleteListFromFile(name);
    fstream watch_lists_file("watch lists.txt", ios::in | ios::out | ios::app);
    if (!watch_lists_file.is_open())
        throw invalid_argument("Failed to open file"); 

    watch_lists_file.seekg(0, ios::end);
    watch_lists_file << name << ":" << endl;
    for (int i = 0; i < num_of_movies; i++)
    {
        watch_lists_file << movies[i].getName() << "," << movies[i].getProductionYear() << "," << Genre::categoryToString(movies[i].getCategory()) << ","
            << movies[i].getEnteredIntoSystemDate().getDay() << "/" << movies[i].getEnteredIntoSystemDate().getMonth() << "/" 
            << movies[i].getEnteredIntoSystemDate().getYear() << "," << movies[i].getLength() << endl;
    }
    watch_lists_file << '%' << endl;
    watch_lists_file.close();
}

void WatchList::writeTVShowsToFile(const string& name) const
{
    fstream watch_lists_file("watch lists.txt", ios::in | ios::out | ios::app);
    if (!watch_lists_file.is_open())
        throw invalid_argument("Failed to open file");

    string line;
    while (getline(watch_lists_file, line)) // Find the user's watch list
    {
        if (line.find(name) != string::npos)
            break;
    }
    while (getline(watch_lists_file, line)) // Skip movies data
    {
        if (line.find('%') != string::npos)
            break;
    }
    for (int i = 0; i < num_of_tvshows; i++)
    {
        watch_lists_file << tvshows[i].getName() << "," << tvshows[i].getProductionYear() << "," << Genre::categoryToString(tvshows[i].getCategory()) << "," << tvshows[i].getEnteredIntoSystemDate().getDay()
            << "/" << tvshows[i].getEnteredIntoSystemDate().getMonth() << "/" << tvshows[i].getEnteredIntoSystemDate().getYear()
            << "," << tvshows[i].getSeasons();
        for (int j = 0; j < tvshows[i].getSeasons(); j++)
        {
            watch_lists_file << "," << tvshows[i].getEpisodes()[j];
        }
        watch_lists_file << endl;
    }
    watch_lists_file.close();
}

void WatchList::deleteListFromFile(const string& name) const
{
    fstream input_file("watch lists.txt", ios::in | ios::out | ios::app);
    if (!input_file.is_open())
        throw invalid_argument("Failed to open file for editing");
    ofstream output_file("tmp.txt", ios::in | ios::out | ios::app);
    if (!output_file.is_open())
        throw invalid_argument("Error creating tmp file for writing");

    string line;
    bool delete_mode = false;
    while (getline(input_file, line))
    {
        if (line.find(name) != string::npos)
        {
            delete_mode = true;
            continue;
        }
        if (line.find(":") != string::npos)
        {
            delete_mode = false;
            output_file << line << endl;
            continue;
        }
        if (!delete_mode)
            output_file << line << endl;
    }
    input_file.close();
    output_file.close();
    if (std::remove("watch lists.txt") != 0)
        throw invalid_argument("Error deleting original file");
    if (std::rename("tmp.txt", "watch lists.txt") != 0)
        throw invalid_argument("Error renaming temporary file");
}

void WatchList::addMovieToWatchList(const Movie& movie)
{
    if (findMovieByName(movie.getName()) == nullptr)
    {
        Movie* new_movies = new Movie[num_of_movies + 1];
        for (int i = 0; i < num_of_movies; i++)
        {
            new_movies[i] = movies[i];
        }
        new_movies[num_of_movies] = movie;
        delete[] movies;
        movies = new_movies;
        num_of_movies++;
        cout << "Movie '" << movie.getName() << "' was succesfully added to watch list" << endl;
    }
    else
        cout << "Movie '" << movie.getName() << "' already exists in watch list" << endl;
}

void WatchList::addTVShowToWatchList(const TVShow& tvshow)
{
    if (findTVShowByName(tvshow.getName()) == nullptr)
    {
        TVShow* new_tvshows = new TVShow[num_of_tvshows + 1];
        for (int i = 0; i < num_of_tvshows; i++)
        {
            new_tvshows[i] = tvshows[i];
        }
        new_tvshows[num_of_tvshows] = tvshow;
        delete[] tvshows;
        tvshows = new_tvshows;
        num_of_tvshows++;
        cout << "TV Show '" << tvshow.getName() << "' was succesfully added to watch list" << endl;
    }
    else
        cout << "TV Show '" << tvshow.getName() << "' already exists in watch list" << endl;
}

void WatchList::deleteMovieByNameFromWatchList(const string& name)
{
    if (movies == nullptr)
        throw invalid_argument("Your watch list has no movies");
    Movie* movie = findMovieByName(name);
    bool found = false;
    if (movie != nullptr)
    {
        for (int i = 0; i < num_of_movies - 1; i++)
        {
            if (movies[i].getName() == movie->getName())
                found = true;
            if (found)
                movies[i] = movies[i + 1];
        }
        num_of_movies--;
        cout << "Movie '" << name << "' was succesfully deleted from watch list" << endl << endl;
    }
    else
        cout << "Movie '" << name << "' does not exist in watch list" << endl << endl;
}

void WatchList::deleteTVShowByNameFromWatchList(const string& name)
{
    if (tvshows == nullptr)
        throw invalid_argument("Your watch list has no tv shows");
    TVShow* tvshow = findTVShowByName(name);
    bool found = false;
    if (tvshow != nullptr)
    {
        for (int i = 0; i < num_of_tvshows - 1; i++)
        {
            if (tvshows[i].getName() == tvshow->getName())
                found = true;
            if (found)
                tvshows[i] = tvshows[i + 1];
        }
        num_of_tvshows--;
        cout << "TV Show '" << name << "' was succesfully deleted from watch list" << endl << endl;
    }
    else
        cout << "TV Show '" << name << "' does not exist in watch list" << endl << endl;
}

Movie* WatchList::findMovieByName(const string& name) const
{
    for (int i = 0; i < num_of_movies; i++)
    {
        if (Item::toLowerCase(movies[i].getName()) == Item::toLowerCase(name))
            return &movies[i];
    }
    return nullptr;
}

TVShow* WatchList::findTVShowByName(const string& name) const
{
    for (int i = 0; i < num_of_tvshows; i++)
    {
        if (Item::toLowerCase(tvshows[i].getName()) == Item::toLowerCase(name))
            return &tvshows[i];
    }
    return nullptr;
}

Movie* WatchList::findMoviesByCategory(const CATEGORY category, int* size) const
{
    if (num_of_movies <= 0)
        return nullptr;
    int count = 0;
    for (int i = 0; i < num_of_movies; i++)
    {
        if (movies[i].getCategory() == category)
            count++;
    }
    *size = count;
    if (count <= 0)
        return nullptr;
    Movie* movies_by_category = new Movie[count];
    int index = 0;
    for (int i = 0; i < num_of_movies; i++)
    {
        if (movies[i].getCategory() == category)
        {
            movies_by_category[index] = movies[i];
            index++;
        }
    }
    return movies_by_category;
}

TVShow* WatchList::findTVShowsByCategory(const CATEGORY category, int* size) const
{
    if (num_of_tvshows <= 0)
        return nullptr;
    int count = 0;
    for (int i = 0; i < num_of_tvshows; i++)
    {
        if (tvshows[i].getCategory() == category)
            count++;
    }
    *size = count;
    if (count <= 0)
        return nullptr;
    TVShow* tvshows_by_category = new TVShow[count];
    int index = 0;
    for (int i = 0; i < num_of_tvshows; i++)
    {
        if (tvshows[i].getCategory() == category)
        {
            tvshows_by_category[index] = tvshows[i];
            index++;
        }
    }
    return tvshows_by_category;
}

Movie WatchList::topOfTheMovieList() const
{
    if (movies == nullptr)
        throw invalid_argument("Your watch list has no movies");
    return movies[0];
}

TVShow WatchList::topOfTheTVShowList() const
{
    if (tvshows == nullptr)
        throw invalid_argument("Your watch list has no tv shows");
    return tvshows[0];     
}

void WatchList::displayMovieList() const
{
    if (movies == nullptr)
        throw invalid_argument("Your watch list has no movies");
    for (int i = 0; i < num_of_movies; i++)
        cout << movies[i].getName() << endl;
}

void WatchList::displayTVShowList() const
{
    if (tvshows == nullptr)
        throw invalid_argument("Your watch list has no tv shows");
    for (int i = 0; i < num_of_tvshows; i++)
        cout << tvshows[i].getName() << endl;
}

void WatchList::display() const
{
    cout << "Movies :" << endl;
    displayMovieList();
    cout << "TV Shows :" << endl;
    displayTVShowList();
}

WatchList::~WatchList()
{
    if (num_of_movies > 0)
    {
        movies = nullptr;
        num_of_movies = 0;
    }
    if (num_of_tvshows > 0)
    {
        tvshows = nullptr;
        num_of_tvshows = 0;
    }
}