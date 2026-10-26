#ifndef ROBOTOMYREQUESTFORM_HPP
#define ROBOTOMYREQUESTFORM_HPP
#include "AForm.hpp"
class RobotomyRequestForm : public AForm {
private:
 const std::string _target;
 RobotomyRequestForm();
public:
 RobotomyRequestForm(const std::string& target);
 RobotomyRequestForm(const RobotomyRequestForm& other);
 ~RobotomyRequestForm();
 RobotomyRequestForm& operator=(const RobotomyRequestForm& other);
 const std::string& getTarget() const;
 void action() const;
};
#endif
