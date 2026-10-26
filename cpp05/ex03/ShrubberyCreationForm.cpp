#include "ShrubberyCreationForm.hpp"
#include <stdexcept>
ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target) : AForm("ShrubberyCreationForm", 145, 137), _target(target) {}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& o) : AForm(o), _target(o._target) {}
ShrubberyCreationForm::~ShrubberyCreationForm() {}
ShrubberyCreationForm& ShrubberyCreationForm::operator=(const ShrubberyCreationForm& o) { if (this != &o) AForm::operator=(o); return *this; }
const std::string& ShrubberyCreationForm::getTarget() const { return _target; }
#include <fstream>
void ShrubberyCreationForm::action() const { std::ofstream out((getTarget() + "_shrubbery").c_str()); if (!out) throw std::runtime_error("could not open output file"); out << "       ,-/-\\\n" << "      / /\\\n" << "     / /  \\n" << "    / /    \\n" << "   /_/______\\\n" << "      ||||\\n"; }
