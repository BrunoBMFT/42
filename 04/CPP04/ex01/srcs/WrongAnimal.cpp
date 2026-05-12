#include "../includes/WrongAnimal.hpp"

const std::string WrongAnimal::getType() const{
	return (type);
}

WrongAnimal::WrongAnimal(){
	type = "defaultWrong";
	std::cout << "WrongAnimal type " << type << " was created\n";
}

WrongAnimal::~WrongAnimal(){
	std::cout << "WrongAnimal default was destructed\n";
}

WrongAnimal::WrongAnimal(const WrongAnimal& other){
	type = other.type;
	std::cout << "WrongAnimal " << type << " was copy constructed\n";
}

WrongAnimal& WrongAnimal::operator=(const WrongAnimal& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "WrongAnimal " << type << " was copy assigned\n";
	return (*this);
}

void	WrongAnimal::makeSound() const{
	std::cout << "Random WrongAnimal Sound!\n";
}