#include "../includes/Bureaucrat.hpp"
#include "../includes/AForm.hpp"
#include "../includes/ShrubberyCreationForm.hpp"
#include "../includes/RobotomyRequestForm.hpp"
#include "../includes/PresidentialPardonForm.hpp"
#include "../includes/Intern.hpp"

int main(void)
{
	srand(time(NULL));

	std::cout << "\n====================================================\n";
	std::cout << "Intern Creating Robotomy Request\n";
	std::cout << "====================================================\n\n";
	Intern	randomIntern;
	AForm*	rrf;
	rrf = randomIntern.makeForm("PresidentialPardonForm", "Crazy Guy");
	// rrf = randomIntern.makeform("robotomy request", "Bender");//subject version
	Bureaucrat highLevel("President", 1);
	highLevel.executeForm(*rrf);
	highLevel.signForm(*rrf);
	highLevel.executeForm(*rrf);

	delete rrf;

	return (0);
}
