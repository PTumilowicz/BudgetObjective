#include "MainController.h"

bool MainController::isUserLoggedIn() { return userManager.isUserLoggedIn(); }

void MainController::registerUser() { userManager.registerUser(); }

void MainController::loginUser()
{
    userManager.loginUser();

    if (userManager.isUserLoggedIn())
    {
        budgetManager = new BudgetManager(INCOME_FILE_NAME, EXPENSE_FILE_NAME, userManager.getLoggedUserId());
    }
}

void MainController::changeUserPassword() { userManager.changeUserPassword(); }

void MainController::logoutUser()
{
    userManager.logoutUser();
    delete budgetManager;
    budgetManager = nullptr;
}

void MainController::addIncome()
{
    if (userManager.isUserLoggedIn())
    {
        budgetManager->addIncome();
    }
}

void MainController::addExpense()
{
    if (userManager.isUserLoggedIn())
    {
        budgetManager->addExpense();
    }
}

void MainController::showCurrentMonthBalance()
{
    if (userManager.isUserLoggedIn())
    {
        budgetManager->showCurrentMonthBalance();
    }
}

void MainController::showPreviousMonthBalance()
{
    if (userManager.isUserLoggedIn())
    {
        budgetManager->showPreviousMonthBalance();
    } 
}

void MainController::showCustomPeriodBalance()
{
    if (userManager.isUserLoggedIn())
    {
        budgetManager->showCustomPeriodBalance();
    }
}
