#include "PhoneBook.hpp"

PhoneBook::PhoneBook(){
	contacts = new Contact[8];
	index = 0;
	contactNum = 0;
}

PhoneBook::~PhoneBook(){
	delete [] contacts;
}

void PhoneBook::AddContact(Contact to_add){
	if (index >= 8)
		index = 0;
	contacts[index] = to_add;
	if (contactNum < 8)
		contactNum++;
	index++;
}

void PhoneBook::Search(){
	if (index < 1){
		std::cout << "Nothing to search, add a contact to start" << std::endl;
		return;
	}
	Contact *temp = contacts;

	std::cout << std::setw(10) << "Index" << "|";
	std::cout << std::setw(10) << "First" << "|";
	std::cout << std::setw(10) << "Last" << "|";
	std::cout << std::setw(10) << "Nickname" << "|" << std::endl;
	for (int i = 0; i < contactNum; i++)
		temp[i].print_Small_Info(i);
	std::string input;
	std::cout << "Select a contact to show: ";
	std::cin.ignore();
	std::getline(std::cin, input);
	int n = atoi(input.c_str()) - 1;
	if (n >= 8 || n < 0 || contactNum <= n){
		std::cout << "No contact with that index" << std::endl;
		return ;
	}
	temp[n].print_Info();
}