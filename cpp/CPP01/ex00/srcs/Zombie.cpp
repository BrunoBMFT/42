#include <Zombie.h>

Zombie::Zombie() {
	this->name = "default";
	std::cout << "Zombie " << this->name << " was born" << std::endl;
}

Zombie::Zombie(std::string _name) : name(_name){
	this->name = _name;
	std::cout << "Zombie " << this->name << " was born" << std::endl;
}

Zombie::~Zombie() {
	std::cout << this->name << " has gone back to sleep." << std::endl;
}

void Zombie::announce(){
	std::cout << this->name << ": BraiiiiiiinnnzzzZ..." << std::endl;
}