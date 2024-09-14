#pragma once
#include <iostream>
#include <string>
#include "AccountsData.h"
using namespace std;

class Menu
{
public:
	static void mainMenu();
	static void AdministratorMenu(Administrator& admin);
	static void userMenu(User& user);
	static int deleteMenu();
	static void findMovieOrTVShow(User& user, Administrator& admin);
	static int yesOrNo();
	static CATEGORY categoryMenu();
	static void clearScreen();
	static int getChoice();
};
