#include "Bureaucrat.hpp"

int main()
{
	try
	{
		Bureaucrat bureaucrat("Alice", 42);
		std::cout << bureaucrat << std::endl;
		bureaucrat.incrementGrade();
		std::cout << bureaucrat << std::endl;
		bureaucrat.decrementGrade();
		std::cout << bureaucrat << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat tooHigh("TooHigh", 0);
		std::cout << tooHigh << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}

	try
	{
		Bureaucrat tooLow("TooLow", 151);
		std::cout << tooLow << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << e.what() << std::endl;
	}
	return 0;
}
