#pragma once
#include <fstream>
#include <iostream>
#include <string>
#include "Administrator.h"
#include "User.h"

class AccountsData
{
private:
	Administrator* admins;
	int num_of_admins;
	User* users;
	int num_of_users;

	void readAdminsFromFile();
	void readUsersFromFile();
	void writeAdminsToFile() const;
	void writeUsersToFile() const;

public:
	AccountsData();
	AccountsData(const AccountsData& data);
	Administrator* findAdmin(const string& name) const;
	User* findUser(const string& name) const;

	~AccountsData();
};
