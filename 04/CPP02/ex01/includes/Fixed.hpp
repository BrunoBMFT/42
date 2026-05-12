#ifndef Fixed_HPP
# define Fixed_HPP

# include <iostream>

class Fixed {
    private:
        int					_raw;
        static const int	_frac = 8;

    public:
        Fixed();
        Fixed(const int);
        Fixed(const float);
        ~Fixed();
        Fixed(const Fixed& other);
        Fixed& operator=(const Fixed& other);

        int		getRawBits(void) const;
        void	setRawBits(int const raw);
        float	toFloat(void) const;
        int		toInt(void) const;
};

std::ostream&	operator<<(std::ostream &o, Fixed const &fixed);

#endif
