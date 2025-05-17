#ifndef Harl_HPP
# define Harl_HPP

# include <iostream>

typedef std::string t_string;

class Harl {
    private:
        void debug(void);
        void info(void);
        void warning(void);
        void error(void);
    public:
        Harl();
        ~Harl();

        void complain (std::string level);
};

#endif
