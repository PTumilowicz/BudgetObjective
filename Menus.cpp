#include "Menus.h"

void Menus::showTitle(std::string title)
{
    system("cls");
    std::cout << ">>>> MY BUDGET -- " << title << " <<<<\n" << std::endl;
}

void Menus::showHomeMenu()
{
    std::cout << "Choose one of the following:\n" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "9. Close app\n" << std::endl;
}

void Menus::showMainMenu()
{
    std::cout << "Choose one of the following:\n" << std::endl;
    std::cout << "1. Add income" << std::endl;
    std::cout << "2. Add expense" << std::endl;
    std::cout << "3. Current month cash balance" << std::endl;
    std::cout << "4. Last month cash balance" << std::endl;
    std::cout << "5. Chosen period cash balance" << std::endl;
    std::cout << "-------------------------------" << std::endl;
    std::cout << "6. Change password" << std::endl;
    std::cout << "8. Logout\n" << std::endl;
}