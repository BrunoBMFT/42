#include "../includes/ClapTrap.h"
#include "../includes/ScavTrap.h"
#include "../includes/FragTrap.h"

int	main(void){
	FragTrap f1("f1");
	FragTrap f2("f2");

	f1.attack("f2");
	f2.attack("f1");
	f2.highFivesGuys();
}