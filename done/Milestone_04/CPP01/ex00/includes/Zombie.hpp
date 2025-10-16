#ifndef Zombie_HPP
# define Zombie_HPP

# include <iostream>

typedef std::string t_string;

class Zombie {
    private:
        std::string name;

    public:
        Zombie();
        Zombie(std::string);
        ~Zombie();

        void announce( void );
    };
    
Zombie *newZombie(std::string name);
void randomChump( std::string name);

#endif
