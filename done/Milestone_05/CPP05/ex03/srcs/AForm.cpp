#include "../includes/AForm.hpp"

AForm::AForm() : _name("default"), _isSigned(false), _toSign(150), _toExec(150) {}
AForm::AForm(std::string name, const int toSign, const int toExec) : 
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
AForm::AForm(const AForm &other) : _name(other.getName()), _isSigned(other.getIsSigned()),
	_toSign(other.getToSign()), _toExec(other.getToExec()) {
	*this = other;
}
AForm &AForm::operator=(const AForm &other) {
	this->_isSigned = other.getIsSigned();
	return *this;
}
std::ostream&	operator<<(std::ostream &out, AForm const &form){
	out	<< form.getName() << "; signed: " << form.getIsSigned()
		<< "; toSign: " << form.getToSign() << "; toExec: " << form.getToExec() << "\n";
	return out;
}
AForm::~AForm() {}

std::string	AForm::getName() const{
	return _name;
}
bool		AForm::getIsSigned() const{
	return _isSigned;
}
int			AForm::getToSign() const{
	return _toSign;
}
int			AForm::getToExec() const{
	return _toExec;
}

void 	AForm::beSigned(Bureaucrat const &bureau){
	if (getToSign() < bureau.getGrade())
		throw GradeTooLowException();
	_isSigned = true;
}
void 	AForm::execute(Bureaucrat const &bureau){
	if (getToExec() < bureau.getGrade())
		throw GradeTooLowException();
	if (getIsSigned() == false)
		throw NotSignedException();
	doAction();
}
void	AForm::doAction() const {
	std::cout << "YOU SHOULDN'T BE HERE!!!\n";
}

const char*	AForm::GradeTooHighException::what() const throw(){
	return ("Grade too high");
}
const char*	AForm::GradeTooLowException::what() const throw(){
	return ("Grade too low");
}
const char*	AForm::NotSignedException::what() const throw(){
	return ("Form cannot be executed because it isn't signed!");
}
