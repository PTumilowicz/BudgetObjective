#pragma once

#include <iostream>
#include <vector>

#include "User.h"
#include "UserFile.h"
#include "Utils.h"
#include "Menus.h"

class UserManager
{
	int loggedUserId;
	std::vector <User> users;
	UserFile userFile;

	bool checkIfLoginExist(const std::string &login);
	User enterUserData();
	void findUserByLogin(const std::string &login, std::vector <User>::iterator &itr);
	void findUserById(std::vector <User>::iterator& itr);

public:
	UserManager(std::string	userFileName) : userFile(userFileName)
	{
		loggedUserId = 0;
		users = userFile.loadUsersFromFile();
	}

	int getLoggedUserId();
	bool isUserLoggedIn();
	
	void registerUser();
	void loginUser();
	void changeUserPassword();
	void logoutUser();
	
};

