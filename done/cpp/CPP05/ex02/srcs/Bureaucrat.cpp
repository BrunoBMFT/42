#include "../includes/Bureaucrat.hpp"

Bureaucrat::Bureaucrat() : _name("default") , _grade(120) {}
Bureaucrat::Bureaucrat(std::string name, int grade) : _name(name) {
	setGrade(grade);
	if (_grade >= 150)
		throw GradeTooLowException();
	else if (_grade < 1)
		throw GradeTooHighException();
}
Bureaucrat::Bureaucrat(const Bureaucrat &other) : _name(other.getName()){
	*this = other;
}
Bureaucrat &Bureaucrat::operator=(const Bureaucrat &other){
	this->_grade = other._grade;
	return *this;
}
std::ostream&	operator<<(std::ostream &o, Bureaucrat const &bureau){
	o << bureau.getName() << ", bureaucrat grade "
	  << bureau.getGrade() << std::endl;
	return o;
}
Bureaucrat::~Bureaucrat() {}

void		Bureaucrat::setGrade(int grade){
	_grade = grade;
}
std::string	Bureaucrat::getName() const{
	return _name;
}
int			Bureaucrat::getGrade() const{
	return _grade;
}

void		Bureaucrat::incrementGrade(){
	if (_grade <= 1)
		throw GradeTooHighException();
	this->_grade--;
}
void		Bureaucrat::decrementGrade(){
	if (_grade >= 150)
		throw GradeTooLowException();
	this->_grade++;
}
void		Bureaucrat::signForm(AForm &form){
	try {
		form.beSigned(*this);
	} catch (const std::exception& e) {
		std::cerr << _name << " couldn't sign " << form.getName()
				  << " because " << e.what() << std::endl;
		return ;
	}
	std::cout << _name << " signed " << form.getName() << std::endl;
}
void		Bureaucrat::executeForm(AForm &form){
	try {
		form.execute(*this);
	} catch (std::exception& e) {
		std::cerr << e.what() << std::endl;
		return ;
	}
	std::cout << _name << " executed " << form.getName() << std::endl;
}

const char*	Bureaucrat::GradeTooHighException::what() const throw(){
	return ("Grade too high");
}
const char*	Bureaucrat::GradeTooLowException::what() const throw(){
	return ("Grade too low");
}
