#include "Array.hpp"
#include <iostream>
#include <string>

int main()
{
	Array<int> empty;
	std::cout << "empty size: " << empty.size() << std::endl;

	Array<int> numbers(3);
	numbers[0] = 10;
	numbers[1] = 20;
	numbers[2] = 30;
	Array<int> copy(numbers);
	numbers[0] = 99;
	std::cout << "copy remains independent: " << copy[0] << std::endl;

	Array<int> assigned;
	assigned = numbers;
	numbers[1] = 77;
	std::cout << "assignment remains independent: " << assigned[1] << std::endl;

	Array<std::string> words(2);
	words[0] = "deep";
	words[1] = "copy";
	std::cout << words[0] << " " << words[1] << std::endl;

	try
	{
		std::cout << numbers[3] << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
