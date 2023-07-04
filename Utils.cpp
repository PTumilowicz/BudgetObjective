#include "Utils.h"

char Utils::getCharacter()
{
    std::string input = "";
    char givenCharacter;

    std::cout << "Your choice: ";

    while (true) {
        std::getline(std::cin, input);

        if (input.length() == 1) {
            givenCharacter = input[0];
            break;
        }
        std::cout << "This is not a single character. Try again." << std::endl;
        system("pause");
    }

    return givenCharacter;
}

std::string Utils::readLine() {
    std::string input = "";
    std::cin.sync();
    std::getline(std::cin, input);
    return input;
}

bool Utils::validateInput(std::string input)
{
    if (input.length() == 0)
    {
        std::cout << "Value cannot be empty. Try again." << std::endl;
        return false;
    }

    if (!std::regex_match(input, std::regex("[\\w]+")))
    {
        std::cout << "Restricted characters used. Only letters, digits and underscore allowed. Try again." << std::endl;
        return false;
    }

    return true;
}