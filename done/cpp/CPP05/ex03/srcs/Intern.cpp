#include "../includes/Intern.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"

Intern::Intern(){}
Intern::Intern(const Intern &other){*this = other;}
Intern &Intern::operator=(const Intern &other){(void)other;return *this;/*nothing to put here I think*/}
Intern::~Intern(){}

AForm*	Intern::makeForm(std::string name, std::string target){
	std::string Forms[3] = {"ShrubberyCreationForm", "RobotomyRequestForm", "PresidentialPardonForm"};
	int i = 0;
	while (i < 3 && Forms[i] != name){
		i++;
	}
	switch (i) {
		case 0:
			std::cout << "Intern creates " << name << std::endl;
			return (new ShrubberyCreationForm(target));
		case 1:
			std::cout << "Intern creates " << name << std::endl;
			return (new RobotomyRequestForm(target));
		case 2:
			std::cout << "Intern creates " << name << std::endl;
			return (new PresidentialPardonForm(target));
		default:
			std::cout << "No form existing with name " << name << std::endl;
			return (NULL);
	}
}