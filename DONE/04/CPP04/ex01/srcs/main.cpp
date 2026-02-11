#include "../includes/Animal.hpp"
#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/Brain.hpp"
#include "../includes/WrongAnimal.hpp"
#include "../includes/WrongCat.hpp"

int	main(void){
	{
		std::cout << "\n|||Testing Array|||\n";
		Animal* animals[4];
		for (int i = 0; i < 2; i++)
			animals[i] = new Dog();
		for (int i = 2; i < 4; i++)
			animals[i] = new Cat();
		for (int i = 0; i < 4; i++)
			std::cout << animals[i]->getType() << "\n";
		for (int i = 0; i < 4; i++)
			animals[i]->makeSound();
		for (int i = 0; i < 4; i++)
			delete animals[i];
	}
	{
		std::cout << "\n|||Testing Ideas|||\n";
		std::cout << "\n[standard construction]\n";
		Cat cat1;
		std::cout << cat1.getBrain()->getIdea(42) << "\n";
		cat1.getBrain()->setIdea(43, "Hello Test 43");
		Cat cat2 = cat1;
		std::cout << "\n[only updated cat1, and did cat2 = cat1]\n";
		std::cout << cat1.getBrain()->getIdea(43) << "\n";
		std::cout << cat2.getBrain()->getIdea(43) << "\n";
		cat1.getBrain()->setIdea(44, "Hello Test 44");
		std::cout << "\n[only updated cat1, nothing else]\n";
		std::cout << cat1.getBrain()->getIdea(44) << "\n";
		std::cout << cat2.getBrain()->getIdea(44) << "\n";
	}


	return 0;
}