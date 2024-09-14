#include "Genre.h"

CATEGORY Genre::stringToCategory(const string& str)
{
    for (int i = 0; i < sizeof(categoryStrings) / sizeof(categoryStrings[0]); i++)
    {
        if (str == categoryStrings[i])
            return categoryEnums[i];
    }
    return CATEGORY::UNKNOWN;
}

string Genre::categoryToString(CATEGORY category)
{
    for (int i = 0; i < sizeof(categoryEnums) / sizeof(categoryEnums[0]); i++)
    {
        if (category == categoryEnums[i])
            return categoryStrings[i];
    }
    return "UNKNOWN";
}