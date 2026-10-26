#include "Bureaucrat.hpp"
#include "ShrubberyCreationForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "PresidentialPardonForm.hpp"
int main() {
 try {
  Bureaucrat alice("Alice", 1);
  ShrubberyCreationForm trees("garden");
  RobotomyRequestForm robot("Bender");
  PresidentialPardonForm pardon("Ford Prefect");
  alice.signForm(trees); alice.executeForm(trees);
  alice.signForm(robot); alice.executeForm(robot);
  alice.signForm(pardon); alice.executeForm(pardon);
 } catch (const std::exception& e) { std::cerr << e.what() << std::endl; }
 return 0;
}
