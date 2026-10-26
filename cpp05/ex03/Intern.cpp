#include "Intern.hpp"
#include "AForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
#include <iostream>
Intern::Intern() {}
Intern::Intern(const Intern&) {}
Intern::~Intern() {}
Intern& Intern::operator=(const Intern&) { return *this; }
AForm* Intern::makeForm(const std::string& name, const std::string& target) const {
 if (name == "shrubbery creation") { std::cout << "Intern creates " << name << std::endl; return new ShrubberyCreationForm(target); }
 if (name == "robotomy request") { std::cout << "Intern creates " << name << std::endl; return new RobotomyRequestForm(target); }
 if (name == "presidential pardon") { std::cout << "Intern creates " << name << std::endl; return new PresidentialPardonForm(target); }
 std::cout << "Intern cannot create " << name << std::endl; return NULL;
}
