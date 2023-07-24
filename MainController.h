#pragma once

#include <iostream>

#include "UserManager.h"
#include "BudgetManager.h"

class MainController
{
	UserManager userManager;
	BudgetManager* budgetManager;
	const std::string INCOME_FILE_NAME;
	const std::string EXPENSE_FILE_NAME;

public:
	MainController(std::string userFileName, std::string incomeFileName, std::string expenseFileName)
		: userManager(userFileName), INCOME_FILE_NAME(incomeFileName), EXPENSE_FILE_NAME(expenseFileName)
	{
		budgetManager = nullptr;
	}

	bool isUserLoggedIn();
	void registerUser();
	void loginUser();
	void changeUserPassword();
	void logoutUser();

	void addIncome();
	void addExpense();
	void showCurrentMonthBalance();
	void showPreviousMonthBalance();
	void showCustomPeriodBalance();
};

