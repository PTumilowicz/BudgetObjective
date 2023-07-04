#include "UserManager.h"

int UserManager::getLoggedUserId()
{
    return this->loggedUserId;
}

bool UserManager::isUserLoggedIn()
{
    return loggedUserId;
}

void UserManager::registerUser()
{
    User user;
    user = enterUserData();

    if (userFile.addUserToFile(user))
    {
        users.push_back(user);
        std::cout << "\nAccount registered!\n" << std::endl;
    }

    system("pause");
}

void UserManager::loginUser()
{
    std::string login, password;
    std::vector <User>::iterator itr;

    Menus::showTitle("LOGIN");
    
    std::cout << "Enter your login: ";
    login = Utils::readLine();

    findUserByLogin(login, itr);

    if (itr != users.end())
    {
        for (size_t i = 0; i < 3; ++i)
        {
            std::cout << "Enter your password: ";
            password = Utils::readLine();

            if (itr->password == password)
            {
                std::cout << "Login successful." << std::endl;
                loggedUserId = itr->id;
                return;
            }
            else
            {
                std::cout << "Password incorrect. You have " << 2 - i << " attempts left." << std::endl;
            }

            if (i == 2)
            {
                std::cout << "Login failed. You will be redirected to Home Menu." << std::endl;
                system("pause");
            }
        }
    }
    else
    {
        std::cout << "Login do not exist. Try again." << std::endl;
        system("pause");
    }
}

void UserManager::changeUserPassword()
{
    std::string oldPassword, newPassword;
    std::vector <User>::iterator itr;

    findUserById(itr);
    
    Menus::showTitle("CHANGE PASSWORD MENU");

    for (size_t i = 0; i < 3; ++i)
    {
        std::cout << "Enter your old password: ";
        oldPassword = Utils::readLine();

        if (itr->password == oldPassword)
        {
            std::cout << "Passwords match. Enter new password: ";
            newPassword = Utils::readLine();

            itr->password = newPassword;
            std::cout << (userFile.changePasswordInFile(loggedUserId, newPassword) ? "Password changed." : "Password not changed. Try again.") << std::endl;
            system("pause");
            return;
        }
        else
        {
            std::cout << "Password incorrect. You have " << 2 - i << " attempts left." << std::endl;
        }

        if (i == 2)
        {
            std::cout << "You did not provide good old password. You will be redirected to Home Menu." << std::endl;
            system("pause");
            return;
        }
    }
}

void UserManager::logoutUser()
{
    loggedUserId = 0;
    std::cout << "\nYou will be logged out. See you again.\n" << std::endl;
    system("pause");
}

bool UserManager::checkIfLoginExist(const std::string &login)
{
    for (const User& user : users)
    {
        if (user.login == login)
        {
            return true;
        }
    }

    return false;
}

User UserManager::enterUserData()
{
    bool loginTaken = true;
    std::string firstName, lastName, login, password;
    User user;

    user.id = userFile.getLastId() + 1;

    Menus::showTitle("REGISTER NEW USER");

    std::cout << "Enter user details\n" << std::endl;

    do
    {
        std::cout << "Enter first name: ";
        firstName = Utils::readLine();
    } while (!Utils::validateInput(firstName));

    user.firstName = firstName;

    do
    {
        std::cout << "Enter last name: ";
        lastName = Utils::readLine();
    } while (!Utils::validateInput(lastName));

    user.lastName = lastName;

    while (loginTaken)
    {
        do
        {
            std::cout << "Enter login: ";
            login = Utils::readLine();
        } while (!Utils::validateInput(login));

        loginTaken = checkIfLoginExist(login);

        if (loginTaken)
        {
            std::cout << "Login already used. Try another." << std::endl;
        }
    }

    user.login = login;

    do
    {
        std::cout << "Enter password: ";
        password = Utils::readLine();
    } while (!Utils::validateInput(password));

    user.password = password;

    return user;
}

void UserManager::findUserByLogin(const std::string &login, std::vector <User>::iterator &itr)
{
    for (itr = users.begin(); itr != users.end(); ++itr)
    {
        if (itr->login == login)
        {
            return;
        }
    }
}

void UserManager::findUserById(std::vector <User>::iterator& itr)
{
    for (itr = users.begin(); itr != users.end(); ++itr)
    {
        if (itr->id == loggedUserId)
        {
            return;
        }
    }
}