#pragma once

#include <iostream>
#include <vector>

#include "File.h"
#include "User.h"
#include "tinyxml2.h"

class UserFile : public File
{
public:
	UserFile(std::string userFileName) : File(userFileName) { };

	std::vector <User> loadUsersFromFile();
	bool addUserToFile(const User &user);
	bool changePasswordInFile(int id, const std::string &password);
};

