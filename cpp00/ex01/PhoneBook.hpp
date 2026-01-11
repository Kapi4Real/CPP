#ifndef PHONEBOOK_HPP
#define PHONEBOOK_HPP

#include "Contact.hpp"

class PhoneBook
{
	private : 
		Contact _contacts[8];
		int _count;
		int _index;

	public :
		PhoneBook();
		void AddContact();
		void SearchContact();
};

#endif
