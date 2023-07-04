#include "OperationFile.h"

std::vector <Operation> OperationFile::loadOperationsFromFile(const int loggedUserId)
{
	Operation operation;
	std::vector <Operation> operations;

	xmlDoc.LoadFile(getFileName().c_str());
	checkRootNode();

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
    tinyxml2::XMLElement* pOperation = pRoot->FirstChildElement();

    while (pOperation != nullptr)
    {
        tinyxml2::XMLElement* pElement = pOperation->FirstChildElement();
        pElement->QueryIntText(&operation.id);

        lastId = operation.id;

        pElement = pElement->NextSiblingElement();
        pElement->QueryIntText(&operation.userId);

        if (operation.userId != loggedUserId)
        {
            pOperation = pOperation->NextSiblingElement();
            continue;
        }

        pElement = pElement->NextSiblingElement();
        pElement->QueryIntText(&operation.date);

        pElement = pElement->NextSiblingElement();
        operation.item = pElement->GetText();

        pElement = pElement->NextSiblingElement();
        pElement->QueryDoubleText(&operation.amount);

        operations.push_back(operation);
        pOperation = pOperation->NextSiblingElement();
    }

	return operations;
}

bool OperationFile::addOperationToFile(const Operation &operation)
{
    xmlDoc.LoadFile(getFileName().c_str());
    checkRootNode();

    tinyxml2::XMLNode* pRoot = xmlDoc.FirstChild();
    tinyxml2::XMLElement* pOperation = xmlDoc.NewElement("Operation");
    pRoot->InsertEndChild(pOperation);

    tinyxml2::XMLElement* pElement = pOperation->InsertNewChildElement("id");
    pElement->SetText(operation.id);

    pElement = pOperation->InsertNewChildElement("userId");
    pElement->SetText(operation.userId);

    pElement = pOperation->InsertNewChildElement("date");
    pElement->SetText(operation.date);

    pElement = pOperation->InsertNewChildElement("item");
    pElement->SetText(operation.item.c_str());

    pElement = pOperation->InsertNewChildElement("amount");
    pElement->SetText(operation.amount);

    tinyxml2::XMLError eResult = xmlDoc.SaveFile(getFileName().c_str());

    if (eResult != tinyxml2::XML_SUCCESS)
    {
        std::cout << eResult << std::endl;
        return false;
    }

    lastId++;
    return true;
}
