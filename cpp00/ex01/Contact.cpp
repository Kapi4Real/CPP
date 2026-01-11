#include "Contact.hpp"

Contact::Contact() {}

void Contact::SetContact(
	const std::string& first,
	const std::string& last,
	const std::string& nick,
	const std::string& number,
	const std::string& secret)
{
	_firstName = first;
	_lastName = last;
	_nickName = nick;
	_phoneNumber = number;
	_darkestSecret = secret;
}


std::string Contact::getFirstName() const { return _firstName; }
std::string Contact::getLastName() const { return _lastName; }
std::string Contact::getNickName() const { return _nickName; }
std::string Contact::getPhoneNumber() const { return _phoneNumber; }
std::string Contact::getDarkestSecret() const { return _darkestSecret; }
