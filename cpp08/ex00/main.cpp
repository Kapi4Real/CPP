#include "easyfind.hpp"
#include <iostream>
#include <list>
#include <vector>

int main()
{
	std::vector<int> values;
	values.push_back(10);
	values.push_back(20);
	values.push_back(20);
	values.push_back(30);
	try
	{
		std::vector<int>::iterator found = easyfind(values, 20);
		std::cout << "first match: " << *found << std::endl;
		*found = 21;
		std::cout << "modified match: " << values[1] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	const std::vector<int>& constValues = values;
	try
	{
		std::vector<int>::const_iterator found = easyfind(constValues, 30);
		std::cout << "const match: " << *found << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	std::list<int> other;
	other.push_back(4);
	other.push_back(8);
	try
	{
		std::cout << "list match: " << *easyfind(other, 8) << std::endl;
		easyfind(other, 99);
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
