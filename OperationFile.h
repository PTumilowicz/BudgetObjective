#pragma once

#include <iostream>
#include <vector>
#include <string>

#include "File.h"
#include "Operation.h"
#include "tinyxml2.h"

class OperationFile : public File
{
public:
	OperationFile(std::string fileName) : File(fileName) { }

	std::vector <Operation> loadOperationsFromFile(const int loggedUserId);
	bool addOperationToFile(const Operation &operation);
};

