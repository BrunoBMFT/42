#include <Zombie.h>

Zombie *zombieHorde(int n, std::string name){
	Zombie *horde = new Zombie[n];

	for (int i = 0; i < n; i++){
		horde[i].name = name;
	}
	return horde;
}