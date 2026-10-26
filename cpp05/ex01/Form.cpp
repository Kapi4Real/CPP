#include "Form.hpp"
#include "Bureaucrat.hpp"

static void checkGrade(int grade)
{
	if (grade < 1)
		throw Form::GradeTooHighException();
	if (grade > 150)
		throw Form::GradeTooLowException();
}

Form::Form() : _name("default"), _isSigned(false), _gradeToSign(150), _gradeToExecute(150) {}

Form::Form(const std::string &name, int gradeToSign, int gradeToExecute) 
    : _name(name), _isSigned(false), _gradeToSign(gradeToSign), _gradeToExecute(gradeToExecute)
{
	checkGrade(_gradeToSign);
	checkGrade(_gradeToExecute);
}

Form::Form(const Form &other) 
    : _name(other._name), _isSigned(other._isSigned), 
      _gradeToSign(other._gradeToSign), _gradeToExecute(other._gradeToExecute) {}

Form::~Form() {}

Form &Form::operator=(const Form &other)
{
	if (this != &other)
	{
		_isSigned = other._isSigned;
	}
	return *this;
}

const std::string& Form::getName() const { return _name; }
bool Form::getIsSigned() const { return _isSigned; }
int Form::getGradeToSign() const { return _gradeToSign; }
int Form::getGradeToExecute() const { return _gradeToExecute; }

void Form::beSigned(const Bureaucrat& bureaucrat)
{
	if (bureaucrat.getGrade() > _gradeToSign)
		throw GradeTooLowException();
	_isSigned = true;
}

const char* Form::GradeTooHighException::what() const throw()
{
	return "Form grade is too high!";
}

const char* Form::GradeTooLowException::what() const throw()
{
	return "Form grade is too low!";
}

std::ostream& operator<<(std::ostream& os, const Form& form)
{
	os << "Form " << form.getName()
	   << ", signed: ";
	if (form.getIsSigned())
		os << "yes";
	else
		os << "no";
	os
	   << ", grade to sign: " << form.getGradeToSign()
	   << ", grade to execute: " << form.getGradeToExecute();
	return os;
}
