#include "../includes/WrongCat.hpp" 

WrongCat::WrongCat(){
	type = "WrongCat";
	std::cout << "WrongAnimal type " << getType() << " was created\n";
}

WrongCat::~WrongCat(){
	std::cout << "WrongAnimal " << getType() << " was destructed\n";
}

WrongCat::WrongCat(const WrongCat& other){
	type = other.type;
	std::cout << "WrongAnimal " << getType() << " was copy constructed\n";
}

WrongCat& WrongCat::operator=(const WrongCat& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "WrongAnimal " << getType() << " was copy assigned\n";
	return (*this);
}

void	WrongCat::makeSound() const{
	std::cout << "WrongMeow\n";
}