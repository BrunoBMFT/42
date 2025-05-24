#include "../includes/DiamondTrap.h"

DiamondTrap::DiamondTrap(){
	_name = "default";
	_hp = FragTrap::getHp();
	_ep = ScavTrap::getEp();
	_ad = FragTrap::getAd();
	std::cout << "Diamond " << _name << " was constructed: ";
	printInfo();
}

DiamondTrap::DiamondTrap(std::string name) : ClapTrap(name + "_clap_name"){
	_name = name;
	_hp = FragTrap::getHp();
	_ep = ScavTrap::getEp();
	_ad = FragTrap::getAd();
	std::cout << "Diamond " << _name << " was constructed: ";
	printInfo();
}

DiamondTrap::~DiamondTrap(){
	std::cout << "Diamond " << _name << " was destructed\n";
}

DiamondTrap::DiamondTrap(const DiamondTrap& other){
	_name = other._name;
	_hp = FragTrap::getHp();
	_ep = ScavTrap::getEp();
	_ad = FragTrap::getAd();
	std::cout << "Diamond " << _name << " was copy constructed: ";
	printInfo();
}

DiamondTrap& DiamondTrap::operator=(const DiamondTrap& other){
	if (this != &other){
		_name = other._name;
		_hp = FragTrap::getHp();
		_ep = ScavTrap::getEp();
		_ad = FragTrap::getAd();
	}
	std::cout << "Diamond " << _name << " was copy assigned: ";
	printInfo();
	return (*this);
}

void DiamondTrap::whoAmI(){
	std::cout << "I am " << _name 
	<< ", inherited from Scav and Frag, which inherited from Clap " 
	<< ClapTrap::_name << std::endl;
}