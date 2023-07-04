#include "DateMethods.h"

bool DateMethods::validateDate(std::string &date)
{
	int year, month, day;
	std::map<std::string, int> currentDate;
	std::stringstream ss;

	calculateCurrentDate(currentDate);

	if (date == "t" || date == "T")
	{
		ss << currentDate["year"] << "-" << (currentDate["month"] < 10 ? "0" : "") << currentDate["month"] << "-" << (currentDate["day"] < 10 ? "0" : "") << currentDate["day"];
		date = ss.str();
		return true;
	}

	if (date.length() != 10)
	{
		std::cout << "Incorrect date format. Try again." << std::endl;
		return false;
	}

	if (!std::regex_match(date, std::regex("[0-9]{4}-[0-9]{2}-[0-9]{2}")))
	{
		std::cout << "Incorrect date format. Try again." << std::endl;
		return false;
	}

	try
	{
		year = std::stoi(date.substr(0, 4));
		month = std::stoi(date.substr(5, 2));
		day = std::stoi(date.substr(8, 2));
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception occurred: " << e.what() << std::endl;
		return false;
	}

	if (year < 2000 || year > currentDate["year"])
	{
		std::cout << "Invalid year. Try again." << std::endl;
		return false;
	}

	if (month > 12 || (year == currentDate["year"] && month > currentDate["month"]))
	{
		std::cout << "Invalid month. Try again." << std::endl;
		return false;
	}

	switch (month)
	{
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			if (day > 31)
			{
				std::cout << "Invalid day. Try again." << std::endl;
				return false;
			}
			break;
		case 4: case 6: case 9: case 11:
			if (day > 30)
			{
				std::cout << "Invalid day. Try again." << std::endl;
				return false;
			}
			break;
		case 2:
			if (DateMethods::isYearLeap(year))
			{
				if (day > 29)
				{
					std::cout << "Invalid day. Try again." << std::endl;
					return false;
				}
			}
			else
			{
				if (day > 28)
				{
					std::cout << "Invalid day. Try again." << std::endl;
					return false;
				}
			}
			break;
		default:
			std::cout << "Invalid day. Try again." << std::endl;
			return false;
	}

	return true;
}

int DateMethods::convertStringDateToInt(const std::string &dateAsString)
{
	int year = 0, month = 0, day = 0;

	try
	{
		year = std::stoi(dateAsString.substr(0, 4));
		month = std::stoi(dateAsString.substr(5, 2));
		day = std::stoi(dateAsString.substr(8, 2));
	}
	catch (const std::exception& e)
	{
		std::cout << "Exception occurred: " << e.what() << std::endl;
		return 0;
	}

	return year * 10000 + month * 100 + day;
}

std::string DateMethods::convertIntDateToStringWithDashes(int dateAsInt)
{
	std::string dateAsString = std::to_string(dateAsInt);
	return dateAsString.substr(0, 4) + '-' + dateAsString.substr(4, 2) + '-' + dateAsString.substr(6, 2);
}

int DateMethods::getCurrentDate()
{
	std::map<std::string, int> currentDate;
	calculateCurrentDate(currentDate);

	return currentDate["year"] * 10000 + currentDate["month"] * 100 + currentDate["day"];
}

int DateMethods::getCurrentMonthFirstDayDate() { return ((DateMethods::getCurrentDate() / 100) * 100) + 1; }

int DateMethods::getPreviousMonthFirstDayDate()
{
	int year, month, day = 1;
	std::map<std::string, int> currentDate;
	calculateCurrentDate(currentDate);

	if (currentDate["month"] == 1)
	{
		month = 12;
		year = currentDate["year"] - 1;
	}
	else
	{
		month = currentDate["month"] - 1;
		year = currentDate["year"];
	}

	return year * 10000 + month * 100 + day;
}

int DateMethods::getPreviousMonthLastDayDate()
{
	int year, month, day = 0;
	std::map<std::string, int> currentDate;
	calculateCurrentDate(currentDate);

	if (currentDate["month"] == 1)
	{
		month = 12;
		year = currentDate["year"] - 1;
		day = 31;
	}
	else
	{
		month = currentDate["month"] - 1;
		year = currentDate["year"];

		switch (month)
		{
			case 1: case 3: case 5: case 7: case 8: case 10: case 12:
				day = 31;
				break;
			case 4: case 6: case 9: case 11:
				day = 30;
				break;
			case 2:
				day = DateMethods::isYearLeap(year) ? 29 : 28;
				break;
		}
	}

	return year * 10000 + month * 100 + day;
}

void DateMethods::calculateCurrentDate(std::map<std::string, int>& currentDate)
{
	auto currentTime = std::chrono::system_clock::now();
	time_t currentDateTime = std::chrono::system_clock::to_time_t(currentTime);

	std::tm currentTm;
	localtime_s(&currentTm, &currentDateTime);

	currentDate["year"] = currentTm.tm_year + 1900;
	currentDate["month"] = currentTm.tm_mon + 1;
	currentDate["day"] = currentTm.tm_mday;
}

bool DateMethods::isYearLeap(int year) { return (year % 4 == 0 && year % 100 != 0) || year % 400 == 0; }