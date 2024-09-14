#include "DataBase.h"
#include "Menu.h"

DataBase::DataBase()
{
    readMoviesFromFile();
    readTVShowsFromFile();
}

DataBase::DataBase(const DataBase& data)
{
    num_of_movies = data.num_of_movies;
    movies = new Movie[num_of_movies];
    for (int i = 0; i < num_of_movies; i++)
    {
        movies[i] = data.movies[i];
    }
    num_of_tvshows = data.num_of_tvshows;
    tvshows = new TVShow[num_of_tvshows];
    for (int i = 0; i < num_of_tvshows; i++)
    {
        tvshows[i] = data.tvshows[i];
    }
}

void DataBase::readMoviesFromFile()
{
    ifstream database_file("database.txt");
    if (!database_file.is_open())
        throw invalid_argument("Failed to open database.txt");

    string line;
    int count = 0;
    while (getline(database_file, line) && line != "%") // Count amount of movies in database
    {
        count++;
    }
    num_of_movies = count;
    database_file.seekg(0, ios::beg);
    movies = new Movie[count];
    if (num_of_movies != 0)
    {
        count = 0;
        while (getline(database_file, line) && line != "%")
        {
            try
            { movies[count] = Movie(line); }
            catch (const invalid_argument& e)
            {
                throw;
            }
            count++;
        }
        sortMovies();
    }
    else
        cout << "There are no Movies in the database" << endl;
    database_file.close();
}

void DataBase::readTVShowsFromFile()
{
    ifstream database_file("database.txt");
    if (!database_file.is_open())
        throw invalid_argument("Failed to open database.txt");
    database_file.seekg(0, ios::beg);
    string line;
    while (getline(database_file, line)) // Skip movies data
    {
        if (line == "%")
            break;
    }
    int count = 0;
    while (getline(database_file, line) && line.find(":") == string::npos) // Count amount of tvshows in user's list
    {
        count++;
    }
    num_of_tvshows = count;
    tvshows = new TVShow[count];

    database_file.clear();
    database_file.seekg(0, ios::beg);
    while (getline(database_file, line)) // Skip all admins data
    {
        if (line == "%")
            break;
    }
    if (num_of_tvshows != 0)
    {
        count = 0;
        while (getline(database_file, line) && line.find(":") == string::npos)
        {
            try
            { tvshows[count] = TVShow(line); }
            catch (const invalid_argument& e)
            {
                throw;
            }
            count++;
        }
        sortTVShows();
    }
    else
        cout << "There are no TV Shows in the database" << endl;
    database_file.close();
}

void DataBase::writeMoviesToFile() const
{
    fstream database_file("database.txt", std::ofstream::out | std::ofstream::trunc);
    if (!database_file.is_open())
        throw std::invalid_argument("Failed to open database.txt");

    for (int i = 0; i < num_of_movies; i++)
    {
        database_file << movies[i].getName() << "," << movies[i].getProductionYear() << "," << Genre::categoryToString(movies[i].getCategory()) 
            << "," << movies[i].getEnteredIntoSystemDate().getDay() << "/" << movies[i].getEnteredIntoSystemDate().getMonth() 
            << "/" << movies[i].getEnteredIntoSystemDate().getYear() << "," << movies[i].getLength() << endl;
    }
    database_file << '%' << endl;
    database_file.close();
}

void DataBase::writeTVShowsToFile() const
{
    fstream database_file("database.txt", std::ios::in | std::ios::out | std::ios::app);
    if (!database_file.is_open())
        throw std::invalid_argument("Failed to open database.txt");

    string line;
    while (getline(database_file, line)) // Skip all movies data
    {
        if (line == "%")
            break;
    }
    for (int i = 0; i < num_of_tvshows; i++)
    {
        database_file << tvshows[i].getName() << "," << tvshows[i].getProductionYear() << "," << Genre::categoryToString(tvshows[i].getCategory()) 
            << "," << tvshows[i].getEnteredIntoSystemDate().getDay() << "/" << tvshows[i].getEnteredIntoSystemDate().getMonth() 
            << "/" << tvshows[i].getEnteredIntoSystemDate().getYear() << "," << tvshows[i].getSeasons();
        for (int j = 0; j < tvshows[i].getSeasons(); j++)
        {
            database_file << "," << tvshows[i].getEpisodes()[j];
        }
        database_file << endl;
    }
    database_file.close();
}

void DataBase::sortMovies()
{
    for (int i = 0; i < num_of_movies - 1; i++)
    {
        for (int j = 0; j < num_of_movies - i - 1; j++)
        {
            // Primary sorting by production year
            if (movies[j].getProductionYear() < movies[j + 1].getProductionYear())
            {
                Movie tmp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = tmp;
            }
            // Secondary sorting by entered into system date
            else if (movies[j].getProductionYear() == movies[j + 1].getProductionYear() && movies[j].getEnteredIntoSystemDate() > movies[j + 1].getEnteredIntoSystemDate())
            {
                Movie tmp = movies[j];
                movies[j] = movies[j + 1];
                movies[j + 1] = tmp;
            }
        }
    }
}

void DataBase::sortTVShows()
{
    for (int i = 0; i < num_of_tvshows - 1; i++)
    {
        for (int j = 0; j < num_of_tvshows - i - 1; j++)
        {
            // Primary sorting by production year
            if (tvshows[j].getProductionYear() < tvshows[j + 1].getProductionYear())
            {
                TVShow tmp = tvshows[j];
                tvshows[j] = tvshows[j + 1];
                tvshows[j + 1] = tmp;
            }
            // Secondary sorting by entered into system date
            else if (tvshows[j].getProductionYear() == tvshows[j + 1].getProductionYear() && tvshows[j].getEnteredIntoSystemDate() > tvshows[j + 1].getEnteredIntoSystemDate())
            {
                TVShow tmp = tvshows[j];
                tvshows[j] = tvshows[j + 1];
                tvshows[j + 1] = tmp;
            }
        }
    }
}

void DataBase::addMovie(const Movie& movie) 
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
        Menu::clearScreen();
        cout << "Movie '" << movie.getName() << "' was succesfully added to database" << endl << endl;
    }
    else
    {
        Menu::clearScreen();
        cout << "Movie '" << movie.getName() << "' already exists in database" << endl << endl;
    }
}

void DataBase::addTVShow(const TVShow& tvshow)
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
        Menu::clearScreen();
        cout << "TV Show '" << tvshow.getName() << "' was succesfully added to database" << endl << endl;
    }
    else
    {
        Menu::clearScreen();
        cout << "TV Show '" << tvshow.getName() << "' already exists in database" << endl << endl;
    }   
}

void DataBase::deleteMovieByName(const string& name)
{
    if (movies == nullptr)
        throw invalid_argument("Database has no movies");
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
        Menu::clearScreen();
        cout << "Movie '" << name << "' was succesfully deleted from database" << endl << endl;
    }
    else
    {
        Menu::clearScreen();
        cout << "Movie '" << name << "' does not exist in database" << endl << endl;
    }       
}

void DataBase::deleteTVShowByName(const string& name)
{
    if (tvshows == nullptr)
        throw invalid_argument("Database has no tv shows");
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
        Menu::clearScreen();
        cout << "TV Show '" << name << "' was succesfully deleted from database" << endl << endl;
    }
    else
    {
        Menu::clearScreen();
        cout << "TV Show '" << name << "' does not exist in database" << endl << endl;
    }   
}

Movie* DataBase::findMovieByName(const string& name) const
{
    for (int i = 0; i < num_of_movies; i++)
    {
        if (Item::toLowerCase(movies[i].getName()) == Item::toLowerCase(name))
            return &movies[i];
    }
    return nullptr;
}

TVShow* DataBase::findTVShowByName(const string& name) const
{
    for (int i = 0; i < num_of_tvshows; i++)
    {
        if (Item::toLowerCase(tvshows[i].getName()) == Item::toLowerCase(name))
            return &tvshows[i];
    }
    return nullptr;
}

Movie* DataBase::findMoviesByCategory(const CATEGORY category, int* size) const
{
    int count = 0;
    for (int i = 0; i < num_of_movies; i++) 
    {
        if (movies[i].getCategory() == category)
            count++;
    }
    *size = count;
    if (count == 0)
        return nullptr;
    Movie* by_category = new Movie[count];
    int index = 0;
    for (int i = 0; i < num_of_movies; ++i) 
    {
        if (movies[i].getCategory() == category)
        {
            by_category[index] = movies[i];   
            index++;
        }
    }
    return by_category;
}

TVShow* DataBase::findTVShowsByCategory(const CATEGORY category, int* size) const
{
    int count = 0;
    for (int i = 0; i < num_of_tvshows; i++)
    {
        if (tvshows[i].getCategory() == category)
            count++;
    }
    *size = count;
    if (count == 0)
        return nullptr;
    TVShow* by_category = new TVShow[count];
    int index = 0;
    for (int i = 0; i < num_of_tvshows; ++i)
    {
        if (tvshows[i].getCategory() == category)
        {
            by_category[index] = tvshows[i];
            index++;
        }
    }
    return by_category;
}

void DataBase::displayMovieList() const
{
    if (movies == nullptr)
        throw invalid_argument("Database has no movies");
    for (int i = 0; i < num_of_movies; i++)
        cout << movies[i].getName() << endl;
}

void DataBase::displayTVShowList() const
{
    if (tvshows == nullptr)
        throw invalid_argument("Database has no tv shows");
    for (int i = 0; i < num_of_tvshows; i++)
        cout << tvshows[i].getName() << endl;
}

DataBase::~DataBase()
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