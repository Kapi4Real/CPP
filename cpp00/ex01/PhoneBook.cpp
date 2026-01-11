#include "PhoneBook.hpp"
#include <iomanip>
#include <cstdlib>

PhoneBook::PhoneBook()
{
	_count = 0;
	_index = 0;
}

static std::string getInput(const std::string& prompt) {
    std::string input;
    do {
	std::cout << prompt;
	std::getline(std::cin, input);
	if (input.empty())
	    std::cout << "Empty input retry !:" << std::endl;
    } while (input.empty());
    return input;
}

void PhoneBook::AddContact()
{
    std::string last = getInput("LastName :");
    std::string first = getInput("FirstName :");
    std::string nick = getInput("NickName :");
    std::string number = getInput("PhoneNumber :");
    std::string secret = getInput("DarkestSecret :");

    _contacts[_index].SetContact(last, first, nick, number, secret);
    _index++;
    if (_index >= 8)
	_index = 0;
    if (_count < 8)
	_count++;

    std::cout << "Contact added !" << std::endl;
}

void PhoneBook::SearchContact()
{
	if (_count == 0)
	{
		std::cout << "PhoneBook is empty !" << std::endl;
		return;
	}

	for (int i = 0;i < _count;i++)
	{
		std::string first = _contacts[i].getFirstName();
		std::string last = _contacts[i].getLastName();
		std::string nick = _contacts[i].getNickName();

		if (first.length() > 10)
			first = first.substr(0,9) + ".";
		if (last.length() > 10)
                        last = last.substr(0,9) + ".";
		if (nick.length() > 10)
                        nick = nick.substr(0,9) + ".";

		std::cout << std::setw(10)<< i + 1<< "|"<< std::setw(10) 
			<< first << "|" << std::setw(10) << last << "|" 
			<< std::setw(10) << nick << std::endl;

	}
	std::string input;
	std::cout << "Enter index of contact :";
	std::getline(std::cin, input);
	int index = std::atoi(input.c_str());

	if (index < 1 || index > _count)
	{
		std::cout << "Invalid index !" << std::endl;
		return;
	}

	const Contact& c = _contacts[index - 1];
	std::cout << "First Name :" << c.getFirstName() << std::endl;
	std::cout << "Last Name :" << c.getLastName() << std::endl;
	std::cout << "Nickname :" << c.getNickName() << std::endl;
	std::cout << "Phone Number :" << c.getPhoneNumber() << std::endl;
	std::cout << "Darkest Secret :" << c.getDarkestSecret() << std::endl;

}
