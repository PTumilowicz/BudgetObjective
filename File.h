#pragma once

#include <iostream>
#include <vector>

#include "tinyxml2.h"

class File
{
	const std::string FILE_NAME;
	
protected:
	int lastId;
	tinyxml2::XMLDocument xmlDoc;

	File(std::string fileName) : FILE_NAME(fileName) { lastId = 0; }

	std::string getFileName();
	void checkRootNode();

public:
	int getLastId();
};

