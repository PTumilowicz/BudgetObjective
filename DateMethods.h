#pragma once

#include <iostream>
#include <chrono>
#include <regex>
#include <map>
#include <sstream>

class DateMethods
{
	static void calculateCurrentDate(std::map<std::string, int> &currentDate);
	static bool isYearLeap(int year);

public:
	static bool validateDate(std::string &date);
	static int convertStringDateToInt(const std::string &dateAsString);
	static std::string convertIntDateToStringWithDashes(int dateAsInt);
	static int getCurrentDate();
	static int getCurrentMonthFirstDayDate();
	static int getPreviousMonthLastDayDate();
	static int getPreviousMonthFirstDayDate();
};

