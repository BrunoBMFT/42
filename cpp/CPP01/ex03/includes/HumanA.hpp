#ifndef HumanA_HPP
# define HumanA_HPP

# include <iostream>
# include <Weapon.hpp>

typedef std::string t_string;

class HumanA {
    private:
        Weapon &weapon;
        std::string name;
    public:
        HumanA(std::string, Weapon&);
        ~HumanA();

        void attack();
};
#endif
