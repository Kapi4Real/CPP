#include "Bureaucrat.hpp"
#include "AForm.hpp"
#include "Intern.hpp"
#include <iostream>
int main() {
 Intern someRandomIntern;
 AForm* form = someRandomIntern.makeForm("robotomy request", "Marvin");
 if (form) {
  try { Bureaucrat boss("Boss", 1); boss.signForm(*form); boss.executeForm(*form); }
  catch (const std::exception& e) { std::cerr << e.what() << std::endl; }
  delete form;
 }
 return 0;
}
