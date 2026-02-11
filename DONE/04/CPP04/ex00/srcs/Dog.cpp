#include "../includes/Dog.hpp" 

Dog::Dog(){
	type = "Dog";
	std::cout << "Animal type " << getType() << " was created\n";
}

Dog::~Dog(){
	std::cout << "Animal " << getType() << " was destructed\n";
}

Dog::Dog(const Dog& other){
	type = other.type;
	std::cout << "Animal " << getType() << " was copy constructed\n";
}

Dog& Dog::operator=(const Dog& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "Animal " << getType() << " was copy assigned\n";
	return (*this);
}

void	Dog::makeSound() const{
	std::cout << "Woof\n";
}