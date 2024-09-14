# Video-Library
C++ Project implementing a video library with login system for different user roles: Admin and User. Each role is assigned unique credentials and has access to specific functionalities within a menu system. 

# Project Overview

This project is a movie and TV show management system that allows administrators to manage a central database of available movies and TV shows, and enables users to create and manage personalized watchlists. The system is built around a text file-based backend, handling user authentication and data management through three core files.

# Features
* **Admin Account:**  
        Admins can log in using a username and password.  
        They can access and modify the database of movies and TV shows.  
        Admins can add, remove, or edit movies and TV shows in the database.  

* **User Account:**  
        Users can log in to access their personalized watchlists.  
        Watchlists are unique for each user and contain movies and TV shows they want to watch.  
        Users can view and update their watchlists.  

* **File Management:**  
  All data is stored in text files:
  
            Accounts.txt: Stores usernames and passwords for both users and admins.  
            Database.txt: Contains the complete list of movies and TV shows.  
            watch lists.txt: Stores individual watchlists for each user.
  Any changes made by the users or admins are saved back to these files upon exiting the program.

# File Descriptions

  * Accounts.txt: Contains login credentials for all users and administrators. Each line includes a username and a password.  
  * Database.txt: Stores the central database of movies and TV shows. Admins have full control over this file.  
  * watch lists.txt: Holds the watchlists for each user. Every user has their own list, which is displayed upon login.  

# How to Use the Program

  1. **Admin Login:**  
        Admins use their username and password to log in.  
        Once logged in, they can view and edit the movie/TV show database.
     
        Admin credentials for testing:  
            * Username: matan, Password: 3150  
            * Username: ron, Password: 2122  

  3. **User Login:**  
        Users log in using their username to access their watchlists.  
        They can view, add, or remove items from their watchlist.
     
        User accounts for testing:  
            Matan, Ron, Erez, Hofit

  5. **Exiting the Program:**  
        Upon exiting, the program automatically saves any changes made to the database or watchlists.  

# Usage Instructions
   1. Launch the program.  
   
   2. You will be presented with a main menu with the following options:  
        * **Admin Login:** Allows an admin to log in and manage the database.  
        * **User Login:** Allows a user to log in and manage their watchlist.  
        * **Exit:** Saves any changes and closes the program.  
    
   3. Follow the on-screen instructions to log in as either an admin or a user.  

# Requirements
  * The project uses plain text files (.txt) for storing data.  
  * Ensure the Accounts.txt, Database.txt, and watch lists.txt files are in the same directory as the program for it to function correctly.

# Project Structure

The project consists of the following files:

    Program Source Code: The main executable file that runs the system.
    Accounts.txt: Stores login credentials.
    Database.txt: Contains the movies and TV shows.
    watch lists.txt: Stores users' watchlists.
