#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"

int main(void)
{
	srand(time(NULL));

	std::cout << "\n====================================================\n";
	std::cout << "Shrubbery Creation Form\n";
	std::cout << "====================================================\n\n";
	Bureaucrat shrub("Shrub Man", 130);
	std::cout << shrub;
	ShrubberyCreationForm shrubberyForm("House");
	std::cout << shrubberyForm;
	shrub.executeForm(shrubberyForm);
	shrub.signForm(shrubberyForm);
	std::cout << shrubberyForm;
	shrub.executeForm(shrubberyForm);

	std::cout << "\n====================================================\n";
	std::cout << "Robotomy Request Form\n";
	std::cout << "====================================================\n\n";
	RobotomyRequestForm robotomyForm("Crazy Man");
	Bureaucrat rob("Robotomy Man", 45);
	rob.executeForm(robotomyForm);
	rob.signForm(robotomyForm);
	rob.executeForm(robotomyForm);
	rob.executeForm(robotomyForm);
	rob.executeForm(robotomyForm);

		
	std::cout << "\n====================================================\n";
	std::cout << "Presidential Pardon Form\n";
	std::cout << "====================================================\n\n";
	PresidentialPardonForm presidentForm("Crazy Man");
	Bureaucrat president("President", 5);
	president.executeForm(presidentForm);
	president.signForm(presidentForm);
	president.executeForm(presidentForm);
	president.signForm(presidentForm);
	president.executeForm(presidentForm);
	
	return (0);
}
