#include <Zombie.h>

int main() {
	Zombie zombie1("Foo");
	zombie1.announce();
	std::cout << std::endl;
	
	Zombie *zombie2 = newZombie("newFoo");
	zombie2->announce();
	std::cout << std::endl;
	
	randomChump("randomFoo");
	std::cout << std::endl;
	
	delete zombie2;
	return 0;
}
