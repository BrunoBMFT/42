#include "Contact.hpp"

void Contact::set_values(std::string _first, std::string _last, std::string _nick, std::string _phone, std::string _secret){
	first = _first;
	last = _last;
	nick = _nick;
	phone = _phone;
	secret = _secret;
}

std::string add_Info_Utils(std::string str) {
	std::string line;
	while (1) {
		std::cout << str;
		if (!std::getline(std::cin, line)){
			if (std::cin.eof()){
				return "" ;
			}
		}
		if (line.empty())
			continue;
		bool valid = true;
		for (size_t i = 0; i < line.length(); i++) {
			if (!isprint(line[i])) {
				valid = false;
				break;
			}
		}
		if (!valid)
			continue ;
		break;
	}
	return (line);
}

bool Contact::Add_info(Contact *contact){
	std::string temp;
	temp = add_Info_Utils("First name: ");
	if (temp.empty() && std::cin.eof()) return (false);
	contact->first = temp;
	temp = add_Info_Utils("Last name: ");
	if (temp.empty() && std::cin.eof()) return(false);
	contact->last = temp;
	temp = add_Info_Utils("Nickname: ");
	if (temp.empty() && std::cin.eof()) return(false);
	contact->nick = temp;
	temp = add_Info_Utils("Phone Number: ");
	if (temp.empty() && std::cin.eof()) return(false);
	contact->phone = temp;
	temp = add_Info_Utils("Secret: ");
	if (temp.empty() && std::cin.eof()) return(false);
	contact->secret = temp;
	return (true);
}

void	print_table(std::string str){
	if (str.length() > 10)
		str = str.substr(0, 9) + ".";
	std::cout << std::setw(10) << str << "|";
}

std::string int_to_string(int n){
	std::stringstream temp;
	temp << n;
	return temp.str();
}

void Contact::print_Small_Info(int i){
	std::cout << std::setw(10) << int_to_string(i + 1) << "|";
	print_table(first);
	print_table(last);
	print_table(nick);
	std::cout << std::endl;
}

void Contact::print_Info(){
	std::cout << "First name: " << first << std::endl;
	std::cout << "Last name: " << last << std::endl;
	std::cout << "Nickname: " << nick << std::endl;
	std::cout << "Phone number: " << phone << std::endl;
	std::cout << "Secret: " << secret << std::endl;
}
