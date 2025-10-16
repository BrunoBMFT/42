#include "../includes/ShrubberyCreationForm.hpp"

ShrubberyCreationForm::ShrubberyCreationForm() : AForm("ShrubberyCreationForm", 145, 137) {}
ShrubberyCreationForm::ShrubberyCreationForm(std::string target) : AForm("ShrubberyCreationForm", 145, 137) , _target(target) {}
ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm &other) {
	*this = other;
}
ShrubberyCreationForm &ShrubberyCreationForm::operator=(const ShrubberyCreationForm &other) {
	_target = other._target;
	return *this;
}
ShrubberyCreationForm::~ShrubberyCreationForm() {}

void	ShrubberyCreationForm::doAction() const {
	std::ofstream out((_target + "_shrubbery").c_str());
	out << "    /\\    \n";
	out << "   /  \\   \n";
	out << "  /    \\  \n";
	out << " /      \\ \n";
	out << "/________\\\n";
	out << "    ||    \n";
	out << "    ||    \n";
	out << "    ||    \n";
	out.close();
}
