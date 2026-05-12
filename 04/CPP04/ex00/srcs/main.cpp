#include "../includes/Animal.hpp"
#include "../includes/Cat.hpp"
#include "../includes/Dog.hpp"
#include "../includes/WrongAnimal.hpp"
#include "../includes/WrongCat.hpp"

int	main(void){
	{
		const Animal* animal = new Animal();
		const Animal* cat = new Cat();
		const Animal* dog = new Dog();

		std::cout << animal->getType() << " " << std::endl;
		std::cout << cat->getType() << " " << std::endl;
		std::cout << dog->getType() << " " << std::endl;
		animal->makeSound();
		cat->makeSound();
		dog->makeSound();
		delete animal;
		delete cat;
		delete dog;
	}
	{
		std::cout << "WRONG TESTS\n\n";
		const WrongAnimal* wronganimal = new WrongAnimal();
		const WrongAnimal* wrongcat = new WrongCat();
		const WrongCat*	realwrongcat = new WrongCat();
		
		std::cout << wronganimal->getType() << " " << std::endl;
		std::cout << wrongcat->getType() << " " << std::endl;
		std::cout << realwrongcat->getType() << " " << std::endl;
		wronganimal->makeSound();
		wrongcat->makeSound();
		realwrongcat->makeSound();
		delete wronganimal;
		delete wrongcat;
		delete realwrongcat;
	}

	return 0;
}