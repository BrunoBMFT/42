#include "../includes/Cat.hpp" 

Cat::Cat(){
	type = "Cat";
	std::cout << "Animal type " << getType() << " was created\n";
}

Cat::~Cat(){
	std::cout << "Animal " << getType() << " was destructed\n";
}

Cat::Cat(const Cat& other){
	type = other.type;
	std::cout << "Animal " << getType() << " was copy constructed\n";
}

Cat& Cat::operator=(const Cat& other){
	if (this != &other){
		type = other.type;
	}
	std::cout << "Animal " << getType() << " was copy assigned\n";
	return (*this);
}

void	Cat::makeSound() const{
	std::cout << "Meow\n";
}