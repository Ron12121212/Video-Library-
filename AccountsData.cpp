#include "AccountsData.h"

AccountsData::AccountsData()
{
    readAdminsFromFile();
    readUsersFromFile();
}

AccountsData::AccountsData(const AccountsData& data)
{
    num_of_admins = data.num_of_admins;
    admins = new Administrator[num_of_admins];
    for (int i = 0; i < num_of_admins; i++)
    {
        admins[i] = data.admins[i];
    }
    num_of_users = data.num_of_users;
    users = new User[num_of_users];
    for (int i = 0; i < num_of_users; i++)
    {
        users[i] = data.users[i];
    }
}

void AccountsData::readAdminsFromFile()
{
    ifstream accounts_file("accounts.txt");
    if (!accounts_file.is_open())
        throw invalid_argument("Failed to open accounts.txt");

    string line;
    int count = 0;
    while (getline(accounts_file, line) && line != "$") // Count amount of admins in file
    {
        count++;
    }
    accounts_file.seekg(0, ios::beg);
    admins = new Administrator[count];
    count = 0;
    while (getline(accounts_file, line) && line != "$") // Create admins from file info
    {
        admins[count] = Administrator(line);
        count++;
    }
    num_of_admins = count;
    accounts_file.close();
}

void AccountsData::readUsersFromFile()
{
    ifstream accounts_file("accounts.txt");
    if (!accounts_file.is_open())
        throw invalid_argument("Failed to open accounts.txt");

    string line;
    int count = 0;
    while (getline(accounts_file, line)) // Skip all admins data
    {
        if (line == "$")
            break;   
    }
    while (getline(accounts_file, line)) // Count amount of users in file
    {
        count++;
    }
    num_of_users = count;
    users = new User[count];
    accounts_file.clear();
    accounts_file.seekg(0, ios::beg); 
    while (getline(accounts_file, line)) // Skip all admins data
    {
        if (line == "$")
            break;
    }
    count = 0;
    while (getline(accounts_file, line))  // Create users from file info
    {
        users[count] = User(line);
        count++;
    }
    accounts_file.close();
}

void AccountsData::writeAdminsToFile() const
{
    fstream accounts_file("accounts.txt", std::ofstream::out | std::ofstream::trunc);
    if (!accounts_file.is_open())
        throw std::invalid_argument("Failed to open accounts.txt");

    for (int i = 0; i < num_of_admins; i++)
    {
        accounts_file << admins[i].getID() << "," << admins[i].getFirstName() << "," << admins[i].getLastName() << "," << admins[i].getPassword() 
            << "," << admins[i].getDate().getDay() << "/" << admins[i].getDate().getMonth() << "/" << admins[i].getDate().getYear() << endl;
    }
    accounts_file << '$' << endl;
    accounts_file.close();
}

void AccountsData::writeUsersToFile() const
{
    fstream accounts_file("accounts.txt", ios::in | ios::out | ios::app);
    if (!accounts_file.is_open())
        throw invalid_argument("Failed to open accounts.txt");

    string line;
    while (getline(accounts_file, line)) // Skip all admins data
    {
        if (line == "$")
            break;
    }
    for (int i = 0; i < num_of_users; i++)
    {
        accounts_file << users[i].getID() << "," << users[i].getFirstName() << "," << users[i].getLastName() << ","
            << users[i].getDate().getDay() << "/" << users[i].getDate().getMonth() << "/" << users[i].getDate().getYear() << endl;
    }
    accounts_file.close();
}

Administrator* AccountsData::findAdmin(const string& name) const
{
    for (int i = 0; i < num_of_admins; i++)
    {
        if (Item::toLowerCase(admins[i].getFirstName()) == Item::toLowerCase(name))
            return &admins[i];
    }
    return nullptr;
}

User* AccountsData::findUser(const string& name) const
{
    for (int i = 0; i < num_of_users; i++)
    {
        if (Item::toLowerCase(users[i].getFirstName()) == Item::toLowerCase(name))
            return &users[i];
    }
    return nullptr;
}

AccountsData::~AccountsData()
{
    try
    {
        writeAdminsToFile();
        writeUsersToFile();
    }
    catch (const invalid_argument& e)
    {
        cout << e.what() << endl;
    }
    if (admins != nullptr)
    {
        delete[] admins;
        admins = nullptr;
    }
    if (users != nullptr)
    {
        delete[] users;
        users = nullptr;
    }
}