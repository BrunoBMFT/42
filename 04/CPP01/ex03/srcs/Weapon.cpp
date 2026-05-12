#include <Weapon.h>

Weapon::Weapon(std::string _type) 
		: type(_type) {}

Weapon::~Weapon() {}


std::string Weapon::getType(){
	return this->type;
}

void Weapon::setType(std::string new_type){
	this->type = new_type;
}
