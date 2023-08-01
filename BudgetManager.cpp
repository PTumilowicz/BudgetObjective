#include "BudgetManager.h"

void BudgetManager::addIncome()
{
    Operation income = addOperationDetails(INCOME);
    if (incomeFile.addOperationToFile(income))
    {
        incomes.push_back(income);
        std::cout << "Income added properly." << std::endl;
        system("pause");
        return;
    }

    std::cout << "Income was not added. Try again." << std::endl;
    system("pause");
}

void BudgetManager::addExpense()
{
    Operation expense = addOperationDetails(EXPENSE);
    if(expenseFile.addOperationToFile(expense))
    {
        expenses.push_back(expense);
        std::cout << "Expense added properly." << std::endl;
        system("pause");
        return;
    }

    std::cout << "Expense was not added. Try again." << std::endl;
    system("pause");
}

void BudgetManager::showCurrentMonthBalance() { showBalance(DateMethods::getCurrentMonthFirstDayDate(), DateMethods::getCurrentDate()); }

void BudgetManager::showPreviousMonthBalance() { showBalance(DateMethods::getPreviousMonthFirstDayDate(), DateMethods::getPreviousMonthLastDayDate()); }

void BudgetManager::showCustomPeriodBalance()
{
    std::string tempDate;
    int startDate, endDate;

    Menus::showTitle("SELECT PERIOD");

    do
    {
        std::cout << "Enter start date. Press 't' if you want to enter current date: ";
        tempDate = Utils::readLine();
    } while (!DateMethods::validateDate(tempDate));

    startDate = DateMethods::convertStringDateToInt(tempDate);

    do
    {
        std::cout << "Enter end date. Press 't' if you want to enter current date: ";
        tempDate = Utils::readLine();
    } while (!DateMethods::validateDate(tempDate));

    endDate = DateMethods::convertStringDateToInt(tempDate);

    if (startDate > endDate)
    {
        std::cout << "\nStart date later than end date. Try again.\n" << std::endl;
        system("pause");
        return;
    }

    showBalance(startDate, endDate);
}

Operation BudgetManager::addOperationDetails(const Type &type)
{
    std::string typeDescription, tempDate, tempAmount;
    Operation operation;

    Menus::showTitle("ADD OPERATION DETAILS");

    switch (type)
    {
        case INCOME:
            operation.id = incomeFile.getLastId() + 1;
            typeDescription = "income";
            break;
        case EXPENSE:
            operation.id = expenseFile.getLastId() + 1;
            typeDescription = "expense";
            break;
    }

    operation.userId = LOGGED_USER_ID;

    do
    {
        std::cout << "Enter " << typeDescription << " date. Press 't' if you want to enter current date: ";
        tempDate = Utils::readLine();
    }
    while (!DateMethods::validateDate(tempDate));

    operation.date = DateMethods::convertStringDateToInt(tempDate);

    std::cout << "Enter " << typeDescription << " name: ";
    operation.item = Utils::readLine();

    do
    {
        std::cout << "Add " << typeDescription << " amount: ";
        tempAmount = Utils::readLine();
    }
    while (!CashMethods::validateAmount(tempAmount));

    operation.amount = stod(tempAmount);

    return operation;
}

void BudgetManager::showBalance(int startDate, int endDate)
{
    Menus::showTitle("SHOW BALANCE");
    std::cout << "Selected period: " << DateMethods::convertIntDateToStringWithDashes(startDate) << " to " << DateMethods::convertIntDateToStringWithDashes(endDate) << std::endl;

    double incomesSum = calculateBalance(startDate, endDate, INCOME);
    double expensesSum = calculateBalance(startDate, endDate, EXPENSE);

    std::cout << "----------------------------------------" << std::endl;
    std::cout << "Icomes sum in selected period: " << incomesSum << " PLN." << std::endl;
    std::cout << "Expenses sum in selected period: " << expensesSum << " PLN." << std::endl;
    std::cout << "\nCash balance in selected period: " << incomesSum - expensesSum << " PLN\n" << std::endl;
    system("pause");
}

double BudgetManager::calculateBalance(int startDate, int endDate, const Type& type)
{
    int counter = 0;
    double sum = 0;
    std::string description = type == INCOME ? "Income" : "Expense";
    std::vector <Operation> operations = type == INCOME ? incomes : expenses;

    sort(operations.begin(), operations.end(), [](Operation& leftOp, Operation& rightOp) { return leftOp.date < rightOp.date; });

    std::cout << std::fixed << std::showpoint << std::setprecision(2);
    std::cout << std::endl << ">> " << description << "s listed in selected period: <<" << std::endl << std::endl;

    for (const Operation& operation : operations)
    {
        if (operation.date >= startDate && operation.date <= endDate)
        {
            std::cout << "No.: " << counter + 1 << std::endl;
            std::cout << description << " date: " << DateMethods::convertIntDateToStringWithDashes(operation.date) << std::endl;
            std::cout << description << " item: " << operation.item << std::endl;
            std::cout << description << " amount: " << operation.amount << std::endl << std::endl;
            sum += operation.amount;
            ++counter;
        }
    }

    if (!counter)
    {
        std::cout << "No " << (char)tolower(description[0]) << description.substr(1) << " recorded in selected date range..." << std::endl << std::endl;
    }

    return sum;
}
