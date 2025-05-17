#ifndef HumanB_HPP
# define HumanB_HPP

# include <iostream>
# include <Weapon.h>

typedef std::string t_string;

class HumanB {
    private:
        Weapon *weapon;
        std::string name;
    public:
        HumanB(std::string);
        ~HumanB();

        void setWeapon(Weapon &_weapon);
        void attack();
};
#endif
