#include "TVShow.h"

TVShow::TVShow(const string& name, int year, CATEGORY category, Date date, int seasons)
{
	try
	{
		setName(name);
		setProductionYear(year);
		setCategory(category);
		setEnteredIntoSystemDate(date);
		setSeasons(seasons);
		setEpisodes();
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

TVShow::TVShow(const string& name, int year, CATEGORY category, Date date, int seasons, int* set_episodes)
{
	try
	{
		setName(name);
		setProductionYear(year);
		setCategory(category);
		setEnteredIntoSystemDate(date);
		setSeasons(seasons);
		episodes = set_episodes;
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

TVShow::TVShow(const TVShow& tvshow)
{
	try
	{
		setName(tvshow.getName());
		setProductionYear(tvshow.getProductionYear());
		setCategory(tvshow.getCategory());
		setEnteredIntoSystemDate(tvshow.getEnteredIntoSystemDate());
		setSeasons(tvshow.getSeasons());
		episodes = tvshow.getEpisodes();
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

TVShow::TVShow(const string& line)
{
	string tvshow_name, tvshow_date_str, tvshow_category_str, episodes_str;
	int tvshow_year, tvshow_seasons;
	int line_pos = 0;

	// Read TV show name
	int next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid TV Show format : " + line);
	tvshow_name = line.substr(line_pos, next_line_pos - line_pos);
	line_pos = next_line_pos + 1;

	// Read TV show year
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid TV Show format : " + line);
	tvshow_year = stoi(line.substr(line_pos, next_line_pos - line_pos));
	line_pos = next_line_pos + 1;

	// Read TV show category
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid TV Show format : " + line);
	tvshow_category_str = line.substr(line_pos, next_line_pos - line_pos);
	CATEGORY tvshow_category = Genre::stringToCategory(tvshow_category_str);
	line_pos = next_line_pos + 1;

	// Read entered into system date
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid TV Show format : " + line);
	tvshow_date_str = line.substr(line_pos, next_line_pos - line_pos);
	line_pos = next_line_pos + 1;

	// Read TV show seasons
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid TV Show format : " + line);
	tvshow_seasons = stoi(line.substr(line_pos, next_line_pos - line_pos));
	line_pos = next_line_pos + 1;

	// Read episodes
	episodes_str = line.substr(line_pos);
	episodes = new int[tvshow_seasons];
	int episode_pos = 0;
	int next_episode_pos;
	for (int i = 0; i < tvshow_seasons; i++)
	{
		next_episode_pos = episodes_str.find(',', episode_pos);
		episodes[i] = stoi(episodes_str.substr(episode_pos, next_episode_pos - episode_pos));
		episode_pos = next_episode_pos + 1;
	}
	try
	{
		setName(tvshow_name);
		setProductionYear(tvshow_year);
		setCategory(tvshow_category);
		setEnteredIntoSystemDate(Date(tvshow_date_str));
		setSeasons(tvshow_seasons);
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

void TVShow::setSeasons(int set_seasons)
{
	if (set_seasons <= 0)
		throw invalid_argument("Error ! invalid number of seasons, most be > 0");
	seasons = set_seasons;
}

void TVShow::setEpisodes()
{
	episodes = new int[seasons];
	int i = 0;
	
	while (i < seasons)
	{
		cout << endl << "Please enter number of episodes for season " << i + 1 << " : ";
		cin >> episodes[i];
		if (episodes[i] <= 0)
			cout << "Error ! invalid value for episode, most be > 0" << endl;
		else
			i++;
	}
}

void TVShow::setProductionYear(int set_year)
{
	if (set_year < 1895 || set_year > 2024)
		throw invalid_argument("Error ! invalid tv show production year, must be between 1928 and 2024");
	production_year = set_year;
}

int TVShow::getSeasons() const
{
    return seasons;
}

int* TVShow::getEpisodes() const
{
    return episodes;
}

void TVShow::display() const
{
	cout << "TV Show: " << name << endl;
	cout << "Year Of Production: " << production_year << endl;
	cout << "Category: " << category << endl; 
	for (int i = 0; i < seasons; i++)
	{
		cout << "Season " << i + 1 << " : " << episodes[i] << " episodes" << endl;
	}
	cout << "Entered into system on : ";
    entered_into_system.displayDate();
    cout << endl;
}