#include "Account.h"

void Account::setID(const string& set_id)
{
    if (set_id.length() != 9)
        throw invalid_argument("Error, invalid id length");
    for (char c : set_id)
    {
        if (c < '0' || c > '9')
            throw invalid_argument("Error ! invalid id, can only contain numbers");
    }
    id = set_id;
}

void Account::setFirstName(const string& set_first_name)
{
    if (set_first_name == "")
        throw invalid_argument("Error ! invalid first name, can not be empty");
    for (char c : set_first_name)
    {
        if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
            throw invalid_argument("Error ! invalid first name, can only contain characters");
    }
    first_name = set_first_name;
}

void Account::setLastName(const string& set_last_name)
{
    if (set_last_name == "")
        throw invalid_argument("Error ! invalid first name, can not be empty");
    for (char c : set_last_name)
    {
        if (c < 'A' || (c > 'Z' && c < 'a') || c > 'z')
            throw invalid_argument("Error ! invalid first name, can only contain characters");
    }
    last_name = set_last_name;
}

void Account::setDateOfBirth(Date set_date)
{
    date_of_birth = set_date;
}

const string& Account::getID() const
{
    return id;
}

const string& Account::getFirstName() const
{
    return first_name;
}

const string& Account::getLastName() const
{
    return last_name;
}

Date Account::getDate() const
{
    return date_of_birth;
}

void Account::display() const
{
    cout << "id: " << id << " , first Name: " << first_name << " , last Name: " << last_name << " , date of birth: ";
    date_of_birth.displayDate();
    cout << endl;
}