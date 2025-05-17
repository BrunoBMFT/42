#include "PhoneBook.hpp"

int main() {
	PhoneBook phonebook;
	Contact new_contact;

	while (1)
	{
		std::string str;
		std::cout << "Commands: ADD, SEARCH, EXIT" << std::endl << "> ";
		std::cin >> str;
		if (std::cin.eof()){
			return 0;
		}
		if (str == "ADD"){
			std::cin.ignore();
			if (!new_contact.Add_info(&new_contact))
				return 0;
			phonebook.AddContact(new_contact);
		}
		else if (str == "SEARCH"){
			phonebook.Search();
		}
		else if (str == "EXIT"){
			std::cout << "exiting" << std::endl;
			break ;
		}
	}
	return 0;
}