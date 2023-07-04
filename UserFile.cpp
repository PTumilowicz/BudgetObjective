#include "UserFile.h"

std::vector<User> UserFile::loadUsersFromFile()
{
    User user;
    std::vector <User> users;

    xmlDoc.LoadFile(getFileName().c_str());
    checkRootNode();

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
    tinyxml2::XMLElement* pUser = pRoot->FirstChildElement();
    
    while (pUser != nullptr)
    {
        tinyxml2::XMLElement* pElement = pUser->FirstChildElement();
        pElement->QueryIntText(&user.id);

        lastId = user.id;

        pElement = pElement->NextSiblingElement();
        user.firstName = pElement->GetText();

        pElement = pElement->NextSiblingElement();
        user.lastName = pElement->GetText();

        pElement = pElement->NextSiblingElement();
        user.login = pElement->GetText();

        pElement = pElement->NextSiblingElement();
        user.password = pElement->GetText();

        users.push_back(user);
        pUser = pUser->NextSiblingElement();
    }

    return users;
}

bool UserFile::addUserToFile(const User &user)
{
    xmlDoc.LoadFile(getFileName().c_str());
    checkRootNode();

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
    tinyxml2::XMLElement* pUser = xmlDoc.NewElement("User");
    pRoot->InsertEndChild(pUser);

    tinyxml2::XMLElement* pElement = pUser->InsertNewChildElement("id");
    pElement->SetText(user.id);

    pElement = pUser->InsertNewChildElement("firstName");
    pElement->SetText(user.firstName.c_str());

    pElement = pUser->InsertNewChildElement("lastName");
    pElement->SetText(user.lastName.c_str());

    pElement = pUser->InsertNewChildElement("login");
    pElement->SetText(user.login.c_str());

    pElement = pUser->InsertNewChildElement("password");
    pElement->SetText(user.password.c_str());

    tinyxml2::XMLError eResult = xmlDoc.SaveFile(getFileName().c_str());

    if (eResult != tinyxml2::XML_SUCCESS)
    {
        std::cout << eResult << std::endl;
        return false;
    }

    lastId++;
    return true;
}

bool UserFile::changePasswordInFile(int id, const std::string& password)
{
    int idFromFile;
    xmlDoc.LoadFile(getFileName().c_str());
    checkRootNode();

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
    tinyxml2::XMLElement* pUser = pRoot->FirstChildElement();

    while (pUser != nullptr)
    {
        tinyxml2::XMLElement* pElement = pUser->FirstChildElement();
        pElement->QueryIntText(&idFromFile);

        if (idFromFile == id)
        {
            pElement = pUser->LastChildElement();
            pElement->SetText(password.c_str());
            tinyxml2::XMLError eResult = xmlDoc.SaveFile(getFileName().c_str());

            if (eResult != tinyxml2::XML_SUCCESS)
            {
                std::cout << eResult << std::endl;
                return false;
            }

            return true;
        }

        pUser = pUser->NextSiblingElement();
    }

    return false;
}
