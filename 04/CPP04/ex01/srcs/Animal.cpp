#include "../includes/Animal.hpp"

Animal::Animal(){
	type = "default";
	std::cout << "Animal type " << type << " was created\n";
}

Animal::~Animal(){
	std::cout << "Animal default was destructed\n";
}

Animal::Animal(const Animal& other){
	type = other.type;
	std::cout << "Animal " << type << " was copy constructed\n";
}

Animal& Animal::operator=(const Animal& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "Animal " << type << " was copy assigned\n";
	return (*this);
}

const std::string Animal::getType() const{
	return (type);
}

void	Animal::makeSound() const{
	std::cout << "Random Animal Sound!\n";
}