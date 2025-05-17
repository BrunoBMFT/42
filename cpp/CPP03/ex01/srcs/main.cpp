#include "../includes/ClapTrap.hpp"
#include "../includes/ScavTrap.hpp"

int	main(void){
	ScavTrap s1;
	ScavTrap s2("s2");

	s1.attack("s2");
	s2.attack("s1");
	s2.beRepaired(2);
	s2.guardGate();
}