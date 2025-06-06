#include <Harl.h>

Harl::Harl() {}

Harl::~Harl() {}

void Harl::debug(void){
	std::cout << "DEBUG\nI love having extra bacon for my 7XL-double-cheese-triple-pickle-special-\
ketchup burger. I really do!" << std::endl;
}
void Harl::info(void){
	std::cout << "INFO\nI cannot believe adding extra bacon costs more money. You didn’t put \
enough bacon in my burger! If you did, I wouldn’t be asking for more!" << std::endl;
}
void Harl::warning(void){
	std::cout << "WARNING\nI think I deserve to have some extra bacon for free. I’ve been coming for \
years whereas you started working here since last month." << std::endl;
}
void Harl::error(void){
	std::cout << "ERROR\nThis is unacceptable! I want to speak to the manager now." << std::endl;
}

void Harl::complain (std::string level){
	typedef void (Harl::*harlPrivFunctions)(void);
	std::string levels[] = {"DEBUG", "INFO", "WARNING", "ERROR"};
	harlPrivFunctions fun[] = { &Harl::debug, &Harl::info, &Harl::warning, &Harl::error};
	for (int i = 0; i < 4; i++){
		if (levels[i] == level){
			(this->*fun[i])();
			return ;
		}
	}
	std::cout << "UNKNOWN: Harl doesn't understand this level." << std::endl;
}