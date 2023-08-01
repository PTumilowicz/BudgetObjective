#include "CashMethods.h"

bool CashMethods::validateAmount(std::string &amount)
{
	int counter = 0, dotPosition;
	std::string decimalRest;

	if (amount.length() == 0)
	{
		std::cout << "Amount field cannot be empty. Try again." << std::endl;
		return false;
	}

	std::replace(amount.begin(), amount.end(), ',', '.');

	counter = std::count(amount.begin(), amount.end(), '.');

	if (counter > 1)
	{
		std::cout << "Incorrect number format. Try again." << std::endl;
		return false;
	}

	for (const char &sign : amount)
	{
		if (!isdigit(sign) && sign != '.')
		{
			std::cout << "Only decimal numbers allowed. Try again." << std::endl;
			return false;
		}
	}

	dotPosition = amount.find('.');

	if (dotPosition != std::string::npos)
	{
		decimalRest = amount.substr(dotPosition + 1);

		if (decimalRest.length() > 2)
		{
			std::cout << "Only numbers with two decimal places allowed. Try again." << std::endl;
			return false;
		}
	}

	return true;
}
