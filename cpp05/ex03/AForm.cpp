#include "AForm.hpp"
#include "Bureaucrat.hpp"
static void checkGrade(int grade) { if (grade < 1) throw AForm::GradeTooHighException(); if (grade > 150) throw AForm::GradeTooLowException(); }
AForm::AForm(const std::string& name, int signGrade, int execGrade) : _name(name), _isSigned(false), _gradeToSign(signGrade), _gradeToExecute(execGrade) { checkGrade(signGrade); checkGrade(execGrade); }
AForm::AForm(const AForm& o) : _name(o._name), _isSigned(o._isSigned), _gradeToSign(o._gradeToSign), _gradeToExecute(o._gradeToExecute) {}
AForm::~AForm() {}
AForm& AForm::operator=(const AForm& o) { if (this != &o) _isSigned = o._isSigned; return *this; }
const std::string& AForm::getName() const { return _name; }
bool AForm::getIsSigned() const { return _isSigned; }
int AForm::getGradeToSign() const { return _gradeToSign; }
int AForm::getGradeToExecute() const { return _gradeToExecute; }
void AForm::beSigned(const Bureaucrat& b) { if (b.getGrade() > _gradeToSign) throw GradeTooLowException(); _isSigned = true; }
void AForm::execute(const Bureaucrat& b) const { if (!_isSigned) throw FormNotSignedException(); if (b.getGrade() > _gradeToExecute) throw GradeTooLowException(); action(); }
const char* AForm::GradeTooHighException::what() const throw() { return "Form grade too high"; }
const char* AForm::GradeTooLowException::what() const throw() { return "Form grade too low"; }
const char* AForm::FormNotSignedException::what() const throw() { return "Form is not signed"; }
std::ostream& operator<<(std::ostream& os, const AForm& f)
{
	os << "Form " << f.getName() << ", signed: ";
	if (f.getIsSigned())
		os << "yes";
	else
		os << "no";
	os << ", grade to sign: " << f.getGradeToSign()
	   << ", grade to execute: " << f.getGradeToExecute();
	return os;
}
