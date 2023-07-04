#pragma once

#include <iostream>
#include <vector>
#include <iomanip>

#include "OperationFile.h"
#include "Operation.h"
#include "Utils.h"
#include "Menus.h"
#include "Type.h"
#include "CashMethods.h"
#include "DateMethods.h"

class BudgetManager
{
	const int LOGGED_USER_ID;
	OperationFile incomeFile;
	OperationFile expenseFile;
	std::vector <Operation> incomes;
	std::vector <Operation> expenses;

	Operation addOperationDetails(const Type &type);
	void showBalance(int startDate, int endDate);
	double calculateBalance(int startDate, int endDate, const Type &type);

public:
	BudgetManager(std::string incomeFileName, std::string expenseFileName, int loggedUserId)
		: LOGGED_USER_ID(loggedUserId), incomeFile(incomeFileName), expenseFile(expenseFileName)
	{
		incomes = incomeFile.loadOperationsFromFile(LOGGED_USER_ID);
		expenses = expenseFile.loadOperationsFromFile(LOGGED_USER_ID);
	}

	void addIncome();
	void addExpense();
	void showCurrentMonthBalance();
	void showPreviousMonthBalance();
	void showCustomPeriodBalance();
	
};

