#include "../includes/Form.hpp"

Form::Form() : _name("default"), _isSigned(false), _toSign(150), _toExec(150) {}
Form::Form(std::string name, const int toSign, const int toExec) : 
	_name(name), _isSigned(false), _toSign(toSign), _toExec(toExec) {
	if (_toSign > 150)
		throw GradeTooLowException();
	else if (_toSign < 1)
		throw GradeTooHighException();
	if (_toExec > 150)
		throw GradeTooLowException();
	else if (_toExec < 1)
		throw GradeTooHighException();
}
Form::Form(const Form &other) : _name(other.getName()), _isSigned(other.getIsSigned()),
	_toSign(other.getToSign()), _toExec(other.getToExec()) {
	*this = other;
}
Form &Form::operator=(const Form &other) {
	this->_isSigned = other.getIsSigned();
	return *this;
}
std::ostream&	operator<<(std::ostream &out, Form const &form){
	out	<< form.getName() << "; signed: " << form.getIsSigned()
		<< "; toSign: " << form.getToSign() << "; toExec: " << form.getToExec() << "\n";
	return out;
}
Form::~Form() {}

std::string	Form::getName() const{
	return _name;
}
bool		Form::getIsSigned() const{
	return _isSigned;
}
int			Form::getToSign() const{
	return _toSign;
}
int			Form::getToExec() const{
	return _toExec;
}

void Form::beSigned(Bureaucrat const &bureau){
	if (getToSign() < bureau.getGrade())
		throw GradeTooLowException();
	_isSigned = true;
}

const char*	Form::GradeTooHighException::what() const throw(){
	return ("Grade too high");
}
const char*	Form::GradeTooLowException::what() const throw(){
	return ("Grade too low");
}