#include "../includes/Bureaucrat.hpp"
#include "../includes/Form.hpp"

int main() {

	/*
	std::cout << "====================================================\n";
	std::cout << "Creation tests\n";
	std::cout << "====================================================\n";
	{
		std::cout << "toSign tests\n";
		try {
			Form normal("Normal", 120, 75);
			std::cout << normal;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form highLimitSign("test", 1, 75);
			std::cout << highLimitSign;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form tooHighSign("test", 0, 75);
			std::cout << tooHighSign;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form lowLimitSign("test", 150, 75);
			std::cout << lowLimitSign;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form tooLowSign("test", 151, 75);
			std::cout << tooLowSign;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << "====================================================\n";
		std::cout << "toExec tests\n";
		try {
			Form normal("Normal", 75, 120);
			std::cout << normal;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form highLimitExec("test", 75, 1);
			std::cout << highLimitExec;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form tooHighExec("test", 75, 0);
			std::cout << tooHighExec;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form lowLimitExec("test", 75, 150);
			std::cout << lowLimitExec;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try {
			Form tooLowExec("test", 75, 151);
			std::cout << tooLowExec;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}*/

	/*
	std::cout << "\n====================================================\n";
	std::cout << "beSigned tests\n";
	std::cout << "====================================================\n\n";
	{
		Bureaucrat highBureau("highBureau", 5);
		std::cout << highBureau;
		Bureaucrat lowBureau("lowBureau", 145);
		std::cout << lowBureau;
		Form lowSignGradeForm("low", 140, 100);
		std::cout << lowSignGradeForm;
		Form highSignGradeForm("low", 10, 100);
		std::cout << highSignGradeForm;
		std::cout << "Tests\n";
		try {
			std::cout << "Trying high sign with high bureaucrat\n";
			highSignGradeForm.beSigned(highBureau);
			std::cout << "success\n";
		} catch (std::exception &e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
		try {
			std::cout << "Trying high sign with low bureaucrat\n";
			highSignGradeForm.beSigned(lowBureau);
			std::cout << "success\n";
		} catch (std::exception &e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
		try {
			std::cout << "Trying low sign with high bureaucrat\n";
			lowSignGradeForm.beSigned(highBureau);
			std::cout << "success\n";
		} catch (std::exception &e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
		try {
			std::cout << "Trying low sign with low bureaucrat\n";
			lowSignGradeForm.beSigned(lowBureau);
			std::cout << "success\n";
		} catch (std::exception &e) {
			std::cout << "Exception caught: " << e.what() << std::endl;
		}
	}*/
	
	std::cout << "\n====================================================\n";
	std::cout << "signForm tests\n";
	std::cout << "====================================================\n\n";
	{
		Bureaucrat highBureau("High Bureaucrat", 5);
		Bureaucrat lowBureau("Low Bureaucrat", 145);
		Form lowForm("High Form", 10, 100);
		Form highForm("Low Form", 140, 100);

		std::cout << "\nAttempt: High Bureaucrat tries to sign High Form\n";
		std::cout << highBureau;
		std::cout << highForm;
		highBureau.signForm(highForm);

		std::cout << "\nAttempt: High Bureaucrat tries to sign Low Form\n";
		std::cout << highBureau;
		std::cout << lowForm;
		highBureau.signForm(lowForm);

		std::cout << "\nAttempt: Low Bureaucrat tries to sign Low Form\n";
		std::cout << lowBureau;
		std::cout << lowForm;
		lowBureau.signForm(lowForm);
		std::cout << "\nAttempt: Low Bureaucrat tries to sign High Form\n";
		std::cout << lowBureau;
		std::cout << highForm;
		lowBureau.signForm(highForm);
		
	}
	
	
	return 0;
}

