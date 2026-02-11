#include "../includes/Cat.hpp" 

Cat::Cat(){
	type = "Cat";
	brain = new Brain();
	std::cout << "Animal type " << getType() << " was created\n";
}

Cat::~Cat(){
	delete brain;
	std::cout << "Animal " << getType() << " was destructed\n";
}

Cat::Cat(const Cat& other){
	type = other.type;
	brain = new Brain(*other.brain);
	std::cout << "Animal " << getType() << " was copy constructed\n";
}

Cat& Cat::operator=(const Cat& other){
	if (this != &other){
		type = other.type;
		delete brain;
		brain = new Brain(*other.brain);
	}
	std::cout << "Animal " << getType() << " was copy assigned\n";
	return (*this);
}

void	Cat::makeSound() const{
	std::cout << "Meow\n";
}

Brain* Cat::getBrain() const {
	return (brain);
}