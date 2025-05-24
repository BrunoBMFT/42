#include "../includes/AAnimal.hpp"

AAnimal::AAnimal(){
	type = "default";
	std::cout << "AAnimal type " << type << " was created\n";
}

AAnimal::~AAnimal(){
	std::cout << "AAnimal default was destructed\n";
}

AAnimal::AAnimal(const AAnimal& other){
	type = other.type;
	std::cout << "AAnimal " << type << " was copy constructed\n";
}

AAnimal& AAnimal::operator=(const AAnimal& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "AAnimal " << type << " was copy assigned\n";
	return (*this);
}

const std::string AAnimal::getType() const{
	return (type);
}

void	AAnimal::makeSound() const{
	std::cout << "Random AAnimal Sound!\n";
}