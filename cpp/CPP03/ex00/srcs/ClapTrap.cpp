#include "../includes/ClapTrap.hpp"

void	ClapTrap::printInfo(){
	std::cout << _hp << " hp, " << _ep << " ep, " 
	<< _ad << " ad\n";
}

ClapTrap::ClapTrap(){
	_name = "default";
	_hp = 10;
	_ep = 10;
	_ad = 0;
	std::cout << "Clap " << _name << " was constructed: ";
	printInfo();
}

ClapTrap::ClapTrap(std::string name){
	_name = name;
	_hp = 10;
	_ep = 10;
	_ad = 0;
	std::cout << "Clap " << _name << " was constructed: ";
	printInfo();
}

ClapTrap::~ClapTrap(){
	std::cout << "Clap " << _name << " was destructed\n";
}

ClapTrap::ClapTrap(const ClapTrap& other){
	_name = other._name;
	_hp = other._hp;
	_ep = other._ep;
	_ad = other._ad;
	std::cout << "Clap " << _name << " was copy constructed: ";
	printInfo();
}

ClapTrap& ClapTrap::operator=(const ClapTrap& other){
	if (this != &other){
		_name = other._name;
		_hp = other._hp;
		_ep = other._ep;
		_ad = other._ad;
	}
	std::cout << "Clap " << _name << " was copy assigned: ";
	printInfo();
	return (*this);
}

void	ClapTrap::attack(const std::string &target){
	if (_ep <= 0 || _hp <= 0){
		std::cout << "ClapTrap " << _name << " cant do anything\n";
		return ;
	}
	std::cout << "ClapTrap " << _name << " attacks " << target 
	<< ", causing " << _ad << " points of damage!\n";
	_ep--;
}

void	ClapTrap::takeDamage(unsigned int amount){
	std::cout << "ClapTrap " << _name << " took " << amount 
	<< " points of damage!\n";
	_hp -= amount;
}

void	ClapTrap::beRepaired(unsigned int amount){
	if (_ep <= 0 || _hp <= 0){
		std::cout << "ClapTrap " << _name << " cant do anything\n";
		return ;
	}
	std::cout << "ClapTrap " << _name << " gets repaired by " 
	<< amount << " points!\n";
	_ep--;
}