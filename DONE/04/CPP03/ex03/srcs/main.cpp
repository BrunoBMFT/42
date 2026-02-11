#include "../includes/ClapTrap.h"
#include "../includes/ScavTrap.h"
#include "../includes/FragTrap.h"
#include "../includes/DiamondTrap.h"
//claptrap name should be the diamond_clap_name
//whoAmI is hard coded
int	main(void){
	/*{
		DiamondTrap d1("John");
		DiamondTrap d2("David");

		d1.whoAmI();
		d2.whoAmI();
		d1.attack("d2");
		d2.takeDamage(30);
		d2.guardGate();
		d1.highFivesGuys();
	}*/
	{
		std::cout << "=== Creating DiamondTrap ===\n";
		DiamondTrap dt("Shiny");

		std::cout << "\n=== Display Identity ===\n";
		dt.whoAmI();

		std::cout << "\n=== Attacking ===\n";
		dt.attack("EnemyBot");

		std::cout << "\n=== Taking Damage ===\n";
		dt.takeDamage(40);

		std::cout << "\n=== Repairing ===\n";
		dt.beRepaired(30);

		std::cout << "\n=== Special Abilities ===\n";
		dt.highFivesGuys();
		dt.guardGate();

		std::cout << "\n=== Finished Testing ===\n";
	}
}