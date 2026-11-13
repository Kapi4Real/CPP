#include "iter.hpp"
#include <iostream>
#include <string>

template <typename T>
void printValue(const T& value)
{
	std::cout << value << " ";
}

void addOne(int& value)
{
	++value;
}

int main()
{
	int values[] = {1, 2, 3, 4};
	iter(values, 4, addOne);
	iter<int>(values, 4, printValue<int>);
	std::cout << std::endl;

	const std::string words[] = {"templates", "work", "with", "const"};
	iter<std::string const>(words, 4, printValue<std::string const>);
	std::cout << std::endl;
	return 0;
}
