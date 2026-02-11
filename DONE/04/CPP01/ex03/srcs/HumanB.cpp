#include <HumanB.h>

HumanB::HumanB(std::string _name) 
		: weapon(NULL), name(_name) {}

HumanB::~HumanB() {}


void HumanB::setWeapon(Weapon &_weapon){
	this->weapon = &_weapon;
}

void HumanB::attack(){
	if (weapon == NULL)
		std::cout << this->name << " tries attacking but has no weapon" << std::endl;
	else
		std::cout << this->name << " attacks with their weapon " << this->weapon->getType() << std::endl;
}
