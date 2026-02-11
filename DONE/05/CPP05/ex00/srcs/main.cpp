#include "../includes/Bureaucrat.hpp"

int main() {

	{
		std::cout << "CREATING TESTS\n";
		try{
			Bureaucrat bur1("Normal", 120);
			std::cout << bur1;
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try{
			Bureaucrat bur2("High", 160);
			std::cout << bur2;
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try{
			Bureaucrat bur3("Zero", 0);
			std::cout << bur3;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try{
			Bureaucrat bur4("Negatives", -40);
			std::cout << bur4;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try{
			Bureaucrat bur5("Working", 99);
			std::cout << bur5;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		try{
			Bureaucrat bur6("1", 1);
			std::cout << bur6;
		} catch (std::exception &e) {
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
	
	{
		std::cout << "====================================================\n";
		std::cout << "INCREMENT TESTS\n";
		Bureaucrat toptest("Top test", 149);
		std::cout << toptest;
		try {
			toptest.decrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << toptest;
		try {
			toptest.decrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << toptest;
		try {
			toptest.decrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}

	{
		std::cout << "====================================================\n";
		std::cout << "DECREMENT TESTS\n";
		Bureaucrat bottomtest("Bottom test", 2);
		std::cout << bottomtest;
		try {
			bottomtest.incrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << bottomtest;
		try {
			bottomtest.incrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
		std::cout << bottomtest;
		try {
			bottomtest.incrementGrade();
		} catch (std::exception &e){
			std::cerr << "Exception caught: " << e.what() << std::endl;
		}
	}
	
	{
		std::cout << "====================================================\n";
		std::cout << "CONSTRUCTOR TESTS\n";
		Bureaucrat bureau1("Test", 130);
		std::cout << bureau1;
		Bureaucrat bureau2(bureau1);
		std::cout << bureau2;
		Bureaucrat bureau3 = bureau1;
		std::cout << bureau3;
	}
	return 0;
}