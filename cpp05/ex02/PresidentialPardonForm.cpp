#include "PresidentialPardonForm.hpp"
#include <stdexcept>
PresidentialPardonForm::PresidentialPardonForm(const std::string& target) : AForm("PresidentialPardonForm", 25, 5), _target(target) {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& o) : AForm(o), _target(o._target) {}
PresidentialPardonForm::~PresidentialPardonForm() {}
PresidentialPardonForm& PresidentialPardonForm::operator=(const PresidentialPardonForm& o) { if (this != &o) AForm::operator=(o); return *this; }
const std::string& PresidentialPardonForm::getTarget() const { return _target; }
#include <iostream>
void PresidentialPardonForm::action() const { std::cout << getTarget() << " has been pardoned by Zaphod Beeblebrox" << std::endl; }
