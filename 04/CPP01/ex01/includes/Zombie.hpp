#ifndef Zombie_HPP
# define Zombie_HPP

# include <iostream>

typedef std::string t_string;

class Zombie {
    private:

    public:
        std::string name;
        Zombie();
        Zombie(std::string);
        ~Zombie();
        void announce(int);

};

Zombie *zombieHorde(int n, std::string name);

#endif
