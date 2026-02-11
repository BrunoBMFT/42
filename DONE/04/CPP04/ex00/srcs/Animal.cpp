#include "../includes/Animal.hpp"

const std::string Animal::getType() const{
	return (type);
}

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

void	Animal::makeSound() const{
	std::cout << "Random Animal Sound!\n";
}