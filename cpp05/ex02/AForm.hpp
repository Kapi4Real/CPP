#ifndef AFORM_HPP
#define AFORM_HPP
#include <exception>
#include <iostream>
#include <string>
class Bureaucrat;
class AForm {
private:
 const std::string _name;
 bool _isSigned;
 const int _gradeToSign;
 const int _gradeToExecute;
 AForm();
public:
 AForm(const std::string& name, int signGrade, int execGrade);
 AForm(const AForm& other);
 virtual ~AForm();
 AForm& operator=(const AForm& other);
 const std::string& getName() const;
 bool getIsSigned() const;
 int getGradeToSign() const;
 int getGradeToExecute() const;
 void beSigned(const Bureaucrat& bureaucrat);
 void execute(const Bureaucrat& executor) const;
 virtual void action() const = 0;
 class GradeTooHighException : public std::exception { public: const char* what() const throw(); };
 class GradeTooLowException : public std::exception { public: const char* what() const throw(); };
 class FormNotSignedException : public std::exception { public: const char* what() const throw(); };
};
std::ostream& operator<<(std::ostream& os, const AForm& form);
#endif
