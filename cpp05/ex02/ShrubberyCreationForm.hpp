#ifndef SHRUBBERYCREATIONFORM_HPP
#define SHRUBBERYCREATIONFORM_HPP
#include "AForm.hpp"
class ShrubberyCreationForm : public AForm {
private:
 const std::string _target;
 ShrubberyCreationForm();
public:
 ShrubberyCreationForm(const std::string& target);
 ShrubberyCreationForm(const ShrubberyCreationForm& other);
 ~ShrubberyCreationForm();
 ShrubberyCreationForm& operator=(const ShrubberyCreationForm& other);
 const std::string& getTarget() const;
 void action() const;
};
#endif
