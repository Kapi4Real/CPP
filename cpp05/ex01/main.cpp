#include "Bureaucrat.hpp"
#include "Form.hpp"

int main()
{
	try
	{
		Bureaucrat bob("Bob", 50);
		Form formA("Form A", 40, 30);
		Form formB("Form B", 60, 50);

		std::cout << bob << std::endl;
		std::cout << formA << std::endl;
		std::cout << formB << std::endl;

		bob.signForm(formA);
		bob.signForm(formB);

		std::cout << formA << std::endl;
		std::cout << formB << std::endl;
	}
	catch (const std::exception& e)
	{
		std::cout << "Error: " << e.what() << std::endl;
	}

	return 0;
}
