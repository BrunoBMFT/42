#include "../includes/ScavTrap.h"

int	ScavTrap::getHp() { return (100); }
int	ScavTrap::getEp() { return (50); }
int	ScavTrap::getAd() { return (20); }

ScavTrap::ScavTrap(){
	_name = "default";
	_hp = getHp();
	_ep = getEp();
	_ad = getAd();
	std::cout << "Scav " << _name << " was constructed: ";
	printInfo();
}

ScavTrap::ScavTrap(std::string name){
	_name = name;
	_hp = getHp();
	_ep = getEp();
	_ad = getAd();
	std::cout << "Scav " << _name << " was constructed: ";
	printInfo();
}

ScavTrap::~ScavTrap(){
	std::cout << "Scav " << _name << " was destructed\n";
}

ScavTrap::ScavTrap(const ScavTrap& other){
	_name = other._name;
	_hp = other._hp;
	_ep = other._ep;
	_ad = other._ad;
	std::cout << "Scav " << _name << " was copy constructed: ";
	printInfo();
}

ScavTrap& ScavTrap::operator=(const ScavTrap& other){
	if (this != &other){
		_name = other._name;
		_hp = other._hp;
		_ep = other._ep;
		_ad = other._ad;
	}
	std::cout << "Scav " << _name << " was copy assigned: ";
	printInfo();
	return (*this);
}

void	ScavTrap::attack(const std::string &target){
	if (_ep <= 0 || _hp <= 0){
		std::cout << "ScavTrap " << _name << " cant do anything\n";
		return ;
	}
	std::cout << "ScavTrap " << _name << " attacks " << target 
	<< ", causing " << _ad << " points of damage!\n";
	_ep--;
}

void	ScavTrap::guardGate(){
	if (_ep <= 0 || _hp <= 0){
		std::cout << "ScavTrap " << _name << " cant do anything\n";
		return ;
	}
	std::cout << "Scav " << _name << " is now in Gate keeper mode\n";
}

