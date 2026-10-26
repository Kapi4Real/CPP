#include "RobotomyRequestForm.hpp"
#include <stdexcept>
RobotomyRequestForm::RobotomyRequestForm(const std::string& target) : AForm("RobotomyRequestForm", 72, 45), _target(target) {}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm& o) : AForm(o), _target(o._target) {}
RobotomyRequestForm::~RobotomyRequestForm() {}
RobotomyRequestForm& RobotomyRequestForm::operator=(const RobotomyRequestForm& o) { if (this != &o) AForm::operator=(o); return *this; }
const std::string& RobotomyRequestForm::getTarget() const { return _target; }
#include <cstdlib>
#include <ctime>
#include <iostream>
void RobotomyRequestForm::action() const { static bool seeded = false; if (!seeded) { std::srand(static_cast<unsigned int>(std::time(NULL))); seeded = true; } std::cout << " drilling noises... " << std::endl; if (std::rand() % 2) std::cout << getTarget() << " has been robotomized successfully" << std::endl; else std::cout << "Robotomy failed for " << getTarget() << std::endl; }
