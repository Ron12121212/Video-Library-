#include "Movie.h"

Movie::Movie(const string& name, int year, CATEGORY category, Date date, int length)
{
	try
	{
		setName(name);
		setProductionYear(year);
		setCategory(category);
		setEnteredIntoSystemDate(date);
		setLength(length);
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

Movie::Movie(const Movie& movie)
{
	try
	{
		setName(movie.getName());
		setProductionYear(movie.getProductionYear());
		setCategory(movie.getCategory());
		setEnteredIntoSystemDate(movie.getEnteredIntoSystemDate());
		setLength(movie.getLength());
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

Movie::Movie(const string& line)
{
	string movie_name, movie_date_str, movie_category_str;
	int movie_year, movie_length;
	int line_pos = 0;

	// Read movie name
	int next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid Movie format : " + line);
	movie_name = line.substr(line_pos, next_line_pos - line_pos);
	line_pos = next_line_pos + 1;

	// Read movie year
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid Movie format : " + line);
	movie_year = stoi(line.substr(line_pos, next_line_pos - line_pos));
	line_pos = next_line_pos + 1;

	// Read movie category
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid Movie format : " + line);
	movie_category_str = line.substr(line_pos, next_line_pos - line_pos);
	CATEGORY movie_category = Genre::stringToCategory(movie_category_str);
	line_pos = next_line_pos + 1;

	// Read entered into system date
	next_line_pos = line.find(',', line_pos);
	if (next_line_pos == string::npos)
		throw invalid_argument("Invalid Movie format : " + line);
	movie_date_str = line.substr(line_pos, next_line_pos - line_pos);
	Date movie_date = Date(movie_date_str);
	line_pos = next_line_pos + 1;

	// Read movie length
	movie_length = stoi(line.substr(line_pos));
	try
	{
		setName(movie_name);
		setProductionYear(movie_year);
		setCategory(movie_category);
		setEnteredIntoSystemDate(movie_date);
		setLength(movie_length);
	}
	catch (const invalid_argument& e)
	{
		throw;
	}
}

void Movie::setLength(int set_length)
{
	if (set_length <= 0)
		throw invalid_argument("Error ! invalid length");
	length = set_length;
}

void Movie::setProductionYear(int set_year)
{
	if (set_year < 1895 || set_year > 2024)
		throw invalid_argument("Error ! invalid movie production year, must be between 1895 and 2024");
	production_year = set_year;
}

int Movie::getLength() const
{
	return length;
}

void Movie::display() const
{
	cout << "Movie: " << name << endl;
	cout << "Year Of Production: " << production_year << endl;
	cout << "Category: " << category << endl;
	cout << "Length: " << length << " minutes" << endl;
	cout << "Entered into system on: ";
	entered_into_system.displayDate();
	cout << endl;
}