#include "PhoneBook.hpp"

int main(void)
{
    PhoneBook phoneBook;
    std::string command;
    while (true)
    {
        std::cout << "Enter command (ADD , SEARCH , EXIT) :";
        std::getline(std::cin, command);

        if (command == "ADD")
            phoneBook.AddContact();
        else if (command == "SEARCH")
            phoneBook.SearchContact();
        else if (command == "EXIT")
            break;
        else
            std::cout << "Invalid command !" << std::endl;
    }
    return 0;
}
