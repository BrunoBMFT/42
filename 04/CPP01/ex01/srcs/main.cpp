#include <Zombie.h>
#include <stdlib.h>

int main(void) {
	int n = 3;

	Zombie *horde = zombieHorde(n, "Zombie");
	for (int i = 0; i < n; i++){
		horde->announce(i);
	}

	delete [] horde;
	std::cout << "The horde of " << n << " zombies was deleted" << std::endl;
	return 0;
}
