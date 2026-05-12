#include "../includes/Brain.hpp"

Brain::Brain(){
	for(int i = 0; i < 100; i++){
        ideas[i] = "Idea!";
	}
	std::cout << "Brain was created\n";
}

Brain::~Brain(){
	std::cout << "Brain was destructed\n";
}

Brain::Brain(const Brain& other){
	for(int i = 0; i < 100; i++){
        ideas[i] = other.ideas[i];
	}
	std::cout << "Brain was copy constructed\n";
}

Brain& Brain::operator=(const Brain& other){
	if (this != &other){
		for(int i = 0; i < 100; i++){
			ideas[i] = other.ideas[i];
		}
	}
	std::cout << "Brain was copy assigned\n";
	return (*this);
}

std::string Brain::getIdea(int n) const{
	return (ideas[n]);
}

void Brain::setIdea(int n, std::string newIdea){
	ideas[n] = newIdea;
}