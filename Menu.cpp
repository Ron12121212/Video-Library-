#include "Menu.h"

#ifdef _WIN32
#include <windows.h> // For Windows
#else
#include <cstdlib>   // For Linux and Mac
#endif

void Menu::mainMenu()
{
    try
    {
        AccountsData account_data;
        Administrator* admin = new Administrator();
        User* user = new User();
        string name, password;
        bool admin_used = false, user_used = false;
        int choice;
        do
        {
            cout << "Welcome!\n";
            cout << "Please select your role:\n";
            cout << "1. Admin\n";
            cout << "2. User\n";
            cout << "3. Exit and save changes\n";
            cout << "Enter your choice: ";
            choice = getChoice();
            clearScreen();
            switch (choice)
            {
            case 1: // Admin
                cout << "ADMIN LOGIN\n";
                cout << "Please enter first name : ";
                cin >> name;
                cout << "Please enter password : ";
                cin.ignore();
                getline(cin, password);
                admin = account_data.findAdmin(name);
                if (admin == nullptr)
                {
                    clearScreen();
                    cout << "No such admin exist\n\n";
                    continue;
                }
                if (!admin->checkPassword(password))
                {
                    clearScreen();
                    cout << "Wrong password\n\n";
                    continue;
                }
                admin_used = true;
                Menu::AdministratorMenu(*admin);
                break;
            case 2: // User
                cout << "USER LOGIN\n";
                cout << "Please enter first name : ";
                cin >> name;
                user = account_data.findUser(name);
                if (user == nullptr)
                {
                    clearScreen();
                    cout << "No such user exist\n\n";
                    continue;
                }
                user_used = true;
                Menu::userMenu(*user);
                break;
            case 3: // Exit and save
                cout << "\nExiting...\n";
                try
                {
                    if (admin_used)
                        admin->writeToFile();
                    if (user_used)
                        user->writeToFile();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            default:
                cout << "Invalid choice. Please try again.\n\n";
                break;
            }
        } while (choice != 3);
    }
    catch (const invalid_argument& e)
    {
        cout << e.what() << endl;
        return;
    }
}

void Menu::AdministratorMenu(Administrator& admin)
{
    clearScreen();
    CATEGORY category;
    int choice, delete_choice;
    do
    {
        cout << "Admin Menu:\n";
        cout << "1. Add a movie to the database\n";
        cout << "2. Add a tv show to the database\n";
        cout << "3. Delete a movie from the database\n";
        cout << "4. Delete a tv show from the database\n";
        cout << "5. Exit to the main menu\n";
        cout << "Enter your choice: ";
        choice = getChoice();
        clearScreen();
        switch (choice)
        {
        case 1: // Add movie 
            try { admin.addNewMovie(); }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 2: // Add tv show
            try { admin.addNewTVShow(); }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3: // Delete movie
            delete_choice = deleteMenu();
            clearScreen();
            switch (delete_choice)
            {
            case 1: // Delete movie by name
                try
                {
                    admin.displayMovieList();
                    admin.deleteMovie();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            case 2: // Delete movie by category 
                int size;
                try 
                { 
                    category = categoryMenu();
                    clearScreen();
                    cout << "Movies by category: " << category << endl << endl;
                    Movie* by_category = admin.findMoviesByCategory(category, &size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << by_category[i].getName() << endl;
                    }
                    admin.deleteMovie();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }       
            break;
        case 4: // Delete tv show
            delete_choice = deleteMenu();
            switch (delete_choice)
            {
            case 1: // Delete tv show by name
                clearScreen();
                try
                {
                    admin.displayTVShowList();
                    admin.deleteTVShow();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            case 2: // Delete tv show by category 
                clearScreen();
                int size;
                try 
                { 
                    category = categoryMenu();
                    clearScreen();
                    cout << "TV Shows by category: " << category << endl << endl;
                    TVShow* by_category = admin.findTVShowsByCategory(category, &size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << by_category[i].getName() << endl;
                    }
                    admin.deleteTVShow();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }
            break;
        case 5: // Exit to main menu
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 5);
}

void Menu::userMenu(User& user)
{
    clearScreen();
    Administrator admin = Administrator();
    CATEGORY category;
    int choice, delete_choice, size;
    do
    {
        cout << "User Menu:\n";
        cout << "1. Add a tv show\n";
        cout << "2. Add a movie\n";
        cout << "3. Search for a movie/tv show\n";
        cout << "4. Watch a tv show\n";
        cout << "5. Watch a movie\n";
        cout << "6. Delete a movie from the watchlist\n";
        cout << "7. Delete a tv show from the watchlist\n";
        cout << "8. Exit to the main menu\n";
        cout << "Enter your choice: ";
        choice = getChoice();
        clearScreen();
        switch (choice)
        {
        case 1: // Add tv show
            try
            {
                category = categoryMenu();
                clearScreen();
                cout << "TV Shows by category: " << category << endl << endl;
                TVShow* by_category = admin.findTVShowsByCategory(category, &size);
                if (size == 0)
                    cout << "You have already added all the tv shows of category " << category << endl;
                for (int i = 0; i < size; i++)
                {
                    if (user.findTVShow(by_category[i].getName()) == nullptr)
                        continue;
                    clearScreen();
                    by_category[i].display();
                    cout << endl << "Would you like to add this tv show to your watch list ?" << endl;
                    if (yesOrNo() == 1)
                        user.addNewTVShow(by_category[i]);
                    cout << endl << "Would you like to continue to the next tv show ?" << endl;
                    if (yesOrNo() == 2)
                    {
                        clearScreen();
                        break;
                    }   
                }
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 2: // Add movie
            try
            {
                category = categoryMenu();
                clearScreen();
                cout << "Movies by category: " << category << endl << endl;
                Movie* by_category = admin.findMoviesByCategory(category, &size);
                if (size == 0)
                    cout << "You have already added all the movies of category " << category << endl;
                for (int i = 0; i < size; i++)
                {
                    if (user.findMovie(by_category[i].getName()) == nullptr)
                        continue;
                    clearScreen();
                    by_category[i].display();
                    cout << endl << "Would you like to add this movie to your watch list ?" << endl;
                    if (yesOrNo() == 1)
                        user.addNewMovie(by_category[i]);
                    cout << endl << "Would you like to continue to the next movie ?" << endl;
                    if (yesOrNo() == 2)
                    {
                        clearScreen();
                        break;
                    }
                }
            }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            break;
        case 3: // Search movie/tv show by name
            findMovieOrTVShow(user, admin);
            break;
        case 4: // Watch tv show
            try { user.watchTVShow(); }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            clearScreen();
            break;
        case 5: // Watch movie
            try { user.watchMovie(); }
            catch (const invalid_argument& e)
            {
                cout << e.what() << endl;
            }
            clearScreen();
            break;
        case 6: // Delete movie
            delete_choice = deleteMenu();
            clearScreen();
            switch (delete_choice)
            {
            case 1: // Delete movie by name
                try 
                { 
                    user.displayMovieWatchlist();
                    user.deleteMovie(); 
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            case 2: // Delete movie by category
                int size;
                try 
                {
                    category = categoryMenu();
                    clearScreen();
                    cout << "Movies by category: " << category << endl << endl;
                    Movie* by_category = user.findMoviesByCategory(category, &size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << by_category[i].getName() << endl;
                    }
                    user.deleteMovie();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }
            break;
        case 7: // Delete tv show
            delete_choice = deleteMenu();
            clearScreen();
            switch (delete_choice)
            {
            case 1: // Delete tv show by name
                try 
                { 
                    user.displayTVShowWatchlist();
                    user.deleteTVShow(); 
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            case 2: // Delete tv show by category 
                int size;
                try
                {
                    category = categoryMenu();
                    clearScreen();
                    cout << "TV Shows by category: " << category << endl << endl;
                    TVShow* by_category = user.findTVShowsByCategory(category, &size);
                    for (int i = 0; i < size; i++)
                    {
                        cout << by_category[i].getName() << endl;
                    }
                    user.deleteTVShow();
                }
                catch (const invalid_argument& e)
                {
                    cout << e.what() << endl;
                }
                break;
            }
            break;
        case 8: //Exit to main menu
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice != 8);
}

int Menu::deleteMenu()
{
    CATEGORY category;
    int choice;
    cout << "Delete Menu:\n";
    cout << "1. Delete by name\n";
    cout << "2. Delete by category\n";
    cout << "3. Back to previous menu\n";
    do
    { 
        cout << "Enter your choice: ";
        choice = getChoice();
        if (choice > 0 && choice < 4)// Delete by name or Delete by category 
        {
            clearScreen();
            return choice;
        }
        cout << "\nInvalid choice. Please try again.\n";
    } while (choice < 1 || choice >3);
}

void Menu::findMovieOrTVShow(User& user, Administrator& admin)
{
    int choice, yn_choice;
    TVShow* tvshow;
    Movie* movie;
    cout << "Movie/TV Show ?\n";
    cout << "1.Movie\n";
    cout << "2.TV Show\n";
    do
    { 
        cout << "Enter your choice: ";
        choice = getChoice();
        clearScreen();
        switch (choice)
        {
        case 1: //Search Movie
            movie= admin.findMovie();
            if (movie != nullptr)
            {
                cout << "Movie was found in database\n";
                cout << "Would you like to add it to your watch list ?\n";
                yn_choice = yesOrNo();
                if (yn_choice == 1)   // add it
                    user.addNewMovie(*movie);
            }
            else
                cout << "Movie was not found in database\n";
            break;
        case 2: //Search tv show
            tvshow = admin.findTvshow();
            if (tvshow != nullptr)
            {
                cout << "TV Show was found in database\n";
                cout << "Would you like to add it to your watch list ?\n";
                yn_choice = yesOrNo();
                if (yn_choice == 1)   // add it
                    user.addNewTVShow(*tvshow);
            }
            else
                cout << "TV Show was not found in database\n";
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice < 1 || choice >2);
}

int Menu::yesOrNo()
{
    int choice;
    cout << "1.Yes\n";
    cout << "2.No\n";
    do
    {
        cout << "Enter your choice: ";
        choice = getChoice();
        if (choice == 1 || choice == 2) // Delete by name or Delete by category 
            return choice;
        clearScreen();
        cout << "Invalid choice. Please try again.\n";
    } while (choice < 1 || choice >2);
}

CATEGORY Menu::categoryMenu()
{
    int choice;
    cout << "1. Science Fiction and Fantasy\n";
    cout << "2. Horror\n";
    cout << "3. Comedy\n";
    cout << "4. Thriller\n";
    cout << "5. Back to previous menu\n";
    do 
    {  
        cout << "Enter your choice: ";
        choice = getChoice();
        switch (choice)
        {
        case 1:
            return CATEGORY::SCIFI_FANTASY;
        case 2:
            return CATEGORY::HORROR;
        case 3:
            return CATEGORY::COMEDY;
        case 4:
            return CATEGORY::THRILLER;
        case 5:
            clearScreen();
            throw invalid_argument("");
        default:
            cout << "Invalid choice. Please try again.\n";
            break;
        }
    } while (choice < 1 || choice > 5);
}

void Menu::clearScreen()
{
#ifdef _WIN32
    system("cls"); // For Windows
#else  
    system("clear"); // For Linux and Mac
#endif
}

int Menu::getChoice()
{
    int choice;
    cin >> choice;
    if (cin.fail())
    {
        cin.clear();
        while (cin.get() != '\n'); // Discard characters until new line is encountered
    }
    return choice;
}