#include "../includes/FragTrap.h"

int	FragTrap::getHp() { return (100); }
int	FragTrap::getEp() { return (100); }
int	FragTrap::getAd() { return (30); }

FragTrap::FragTrap(){
	_name = "default";
	_hp = getHp();
	_ep = getEp();
	_ad = getAd();
	std::cout << "Frag " << _name << " was constructed: ";
	printInfo();
}

FragTrap::FragTrap(std::string name){
	_name = name;
	_hp = getHp();
	_ep = getEp();
	_ad = getAd();
	std::cout << "Frag " << _name << " was constructed: ";
	printInfo();
}

FragTrap::~FragTrap(){
	std::cout << "Frag " << _name << " was destructed\n";
}

FragTrap::FragTrap(const FragTrap& other){
	_name = other._name;
	_hp = other._hp;
	_ep = other._ep;
	_ad = other._ad;
	std::cout << "Frag " << _name << " was copy constructed: ";
	printInfo();
}

FragTrap& FragTrap::operator=(const FragTrap& other){
	if (this != &other){
		_name = other._name;
		_hp = other._hp;
		_ep = other._ep;
		_ad = other._ad;
	}
	std::cout << "Frag " << _name << " was copy assigned: ";
	printInfo();
	return (*this);
}

void	FragTrap::attack(const std::string &target){
	std::cout << "should I attack?\n";
	if (_ep <= 0 || _hp <= 0){
		std::cout << "Frag " << _name << " cant do anything\n";
		return ;
	}
	std::cout << "Frag " << _name << " attacks " << target 
	<< ", causing " << _ad << " points of damage!\n";
	_ep--;
}

void	FragTrap::highFivesGuys(){
	std::cout << "Frag " << _name << " High Fives Everyone\n";
}

