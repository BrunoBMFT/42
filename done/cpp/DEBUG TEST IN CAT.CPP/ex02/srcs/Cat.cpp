#include "../includes/Cat.hpp"
// #define DEBUG

#ifdef DEBUG
# define DEBUF_FUN(str) std::cout << str
#endif
#ifndef DEBUG
# define DEBUF_FUN(str) str
#endif



void	debug_fun(std::string str){
	#ifdef DEBUG
	std::cout << str;
	#endif
	DEBUF_FUN(1);
	DEBUF_FUN("hello");
}

Cat::Cat(){
	type = "Cat";
	brain = new Brain();
	#ifdef DEBUG
	std::cout << "Animal type " << getType() << " was created\n";
	#endif
}

Cat::~Cat(){
	delete brain;
	debug_fun("Animal " + getType() + " was destructed\n");
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