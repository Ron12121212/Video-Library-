#pragma once
#include <string>
#include <iostream>
using namespace std;

enum class CATEGORY { SCIFI_FANTASY, HORROR, COMEDY, THRILLER, UNKNOWN };
const string categoryStrings[] = { "SCIFI_FANTASY", "HORROR", "COMEDY", "THRILLER" };
const CATEGORY categoryEnums[] = { CATEGORY::SCIFI_FANTASY, CATEGORY::HORROR, CATEGORY::COMEDY, CATEGORY::THRILLER };

class Genre
{
public:
	static CATEGORY stringToCategory(const std::string& str);
    static string categoryToString(CATEGORY category);
};

static ostream& operator<<(ostream& os, CATEGORY category)
{
    switch (category)
    {
    case CATEGORY::SCIFI_FANTASY:
        os << "Science Fiction and Fantasy";
        break;
    case CATEGORY::HORROR:
        os << "Horror";
        break;
    case CATEGORY::COMEDY:
        os << "Comedy";
        break;
    case CATEGORY::THRILLER:
        os << "Thriller";
        break;
    default:
        os << "Unknown";
        break;
    }
    return os;
}