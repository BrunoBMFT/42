#include <Zombie.h>

Zombie::Zombie() {
	this->name = "default";
	std::cout << "Zombie " << this->name << " was born" << std::endl;
}

Zombie::Zombie(std::string _name) {
	this->name = _name;
	std::cout << "Zombie " << this->name << " was born" << std::endl;
}

Zombie::~Zombie() {
	std::cout << this->name << " has gone back to sleep." << std::endl;
}


void Zombie::announce(int n){
	std::cout << this->name << " " << n + 1 << ": BraiiiiiiinnnzzzZ... " << std::endl;
}