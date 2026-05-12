#include "../includes/PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm() : AForm("PresidentialPardonForm", 25, 5) {}
PresidentialPardonForm::PresidentialPardonForm(std::string target) : AForm("PresidentialPardonForm", 25, 5) , _target(target) {}
PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm &other) {
	*this = other;
}
PresidentialPardonForm &PresidentialPardonForm::operator=(const PresidentialPardonForm &other) {
	_target = other._target;
	return *this;
}
PresidentialPardonForm::~PresidentialPardonForm() {}

void	PresidentialPardonForm::doAction() const {
	std::cout << _target << " has been pardoned by Zaphod Beeblebrox.\n";
}
