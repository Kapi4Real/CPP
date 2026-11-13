#include "Span.hpp"
#include <iostream>
#include <vector>

int main()
{
	try
	{
		Span sample(5);
		sample.addNumber(6);
		sample.addNumber(3);
		sample.addNumber(17);
		sample.addNumber(9);
		sample.addNumber(11);
		std::cout << "sample shortest: " << sample.shortestSpan() << std::endl;
		std::cout << "sample longest: " << sample.longestSpan() << std::endl;

		Span bulk(10000);
		std::vector<int> numbers;
		for (int i = 0; i < 10000; ++i)
			numbers.push_back(i * 3);
		bulk.addNumbers(numbers.begin(), numbers.end());
		std::cout << "10,000 shortest: " << bulk.shortestSpan() << std::endl;
		std::cout << "10,000 longest: " << bulk.longestSpan() << std::endl;

		Span emptySpan;
		try
		{
			emptySpan.longestSpan();
		}
		catch (const std::exception& e)
		{
			std::cout << "empty Span: " << e.what() << std::endl;
		}

		try
		{
			bulk.addNumber(42);
		}
		catch (const std::exception& e)
		{
			std::cout << "full Span: " << e.what() << std::endl;
		}

		Span tooSmall(1);
		tooSmall.addNumber(7);
		try
		{
			tooSmall.shortestSpan();
		}
		catch (const std::exception& e)
		{
			std::cout << "one number: " << e.what() << std::endl;
		}

		Span transactional(2);
		std::vector<int> tooMany;
		tooMany.push_back(1);
		tooMany.push_back(2);
		tooMany.push_back(3);
		try
		{
			transactional.addNumbers(tooMany.begin(), tooMany.end());
		}
		catch (const std::exception& e)
		{
			std::cout << "range rejected: " << e.what() << std::endl;
		}
		transactional.addNumber(4);
		transactional.addNumber(9);
		std::cout << "after rejected range: " << transactional.shortestSpan() << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
