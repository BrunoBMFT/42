#include "../includes/ClapTrap.hpp"

int	main(void){
	{
		ClapTrap c1;
		ClapTrap c2("c2");
		ClapTrap c3(c1);
		ClapTrap c4 = c2;

		c3.attack("c4");
		c4.takeDamage(3);
		c4.beRepaired(3);
	}
	/*{
		ClapTrap c3("c3");
		ClapTrap c4("c4");
		c3.attack("test");
		c4.takeDamage(4);
		c4.attack("c3");
		c3.attack("test");
		c4.takeDamage(4);
		c4.attack("c3");
		c3.attack("test");
		c4.takeDamage(4);
		c4.attack("c3");
		c3.attack("test");
		c4.takeDamage(4);
		c4.attack("c3");
		c3.attack("test");
		c4.takeDamage(4);
		c4.attack("c3");
	}*/
}