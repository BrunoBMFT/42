#include "../includes/RobotomyRequestForm.hpp"

RobotomyRequestForm::RobotomyRequestForm() : AForm("RobotomyRequestForm", 72, 45) {}
RobotomyRequestForm::RobotomyRequestForm(std::string target) : AForm("RobotomyRequestForm", 72, 45) , _target(target) {}
RobotomyRequestForm::RobotomyRequestForm(const RobotomyRequestForm &other) {
	*this = other;
}
RobotomyRequestForm &RobotomyRequestForm::operator=(const RobotomyRequestForm &other) {
	_target = other._target;
	return *this;
}
RobotomyRequestForm::~RobotomyRequestForm() {}

void	RobotomyRequestForm::doAction() const {
	int	random;

	random = rand() % 2;
	if (random == 1)
		std::cout << _target << " has been Robotomized!\n";
	else
		std::cout << "Robotomy Failed!\n";
}
