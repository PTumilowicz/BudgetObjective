#include <iostream>

#include "MainController.h"
#include "Menus.h"

int main()
{
    MainController mainController("users.xml", "incomes.xml", "expenses.xml");

    char choice;

    while (true) {
        if (!mainController.isUserLoggedIn())
        {
            Menus::showTitle("HOME MENU");
            Menus::showHomeMenu();

            choice = Utils::getCharacter();

            switch (choice)
            {
            case '1':
                mainController.loginUser();
                break;
            case '2':
                mainController.registerUser();
                break;
            case '9':
                std::cout << "\nSee you next time.\n";
                exit(0);
                break;
            default:
                std::cout << "\nCharacter not used. Try again.\n" << std::endl;
                system("pause");
                break;
            }
        }
        else
        {
            Menus::showTitle("MAIN MENU");
            Menus::showMainMenu();

            choice = Utils::getCharacter();

            switch (choice)
            {
            case '1':
                mainController.addIncome();
                break;
            case '2':
                mainController.addExpense();
                break;
            case '3':
                mainController.showCurrentMonthBalance();
                break;
            case '4':
                mainController.showPreviousMonthBalance();
                break;
            case '5':
                mainController.showCustomPeriodBalance();
                break;
            case '6':
                mainController.changeUserPassword();
                break;
            case '8':
                mainController.logoutUser();
                break;
            default:
                std::cout << "\nCharacter not used. Try again.\n" << std::endl;
                system("pause");
                break;
            }
        }
    }
}