#ifndef Weapon_HPP
# define Weapon_HPP

# include <iostream>

typedef std::string t_string;

class Weapon {
    private:
        std::string type;

    public:
        Weapon();
        Weapon(std::string);
        ~Weapon();
        Weapon(const Weapon& other);
        Weapon& operator=(const Weapon& other);

        std::string getType();
        void setType(std::string);
};
#endif
