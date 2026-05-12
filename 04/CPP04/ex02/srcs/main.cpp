#include "../includes/AAnimal.hpp"
#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Brain.hpp"

int	main(void){
	{
		std::cout << "NORMAL TESTS\n\n";
		const AAnimal* cat = new Cat();
		const AAnimal* dog = new Dog();

		std::cout << cat->getType() << " " << std::endl;
		std::cout << dog->getType() << " " << std::endl;
		cat->makeSound();
		dog->makeSound();
		delete cat;
		delete dog;
		//ABSTRACT
		// const AAnimal* animal = new AAnimal();
		// std::cout << animal->getType() << " " << std::endl;
		// animal->makeSound();
		// delete animal;
	}

	return 0;
}