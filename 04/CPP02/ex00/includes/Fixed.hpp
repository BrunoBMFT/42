#ifndef Fixed_HPP
# define Fixed_HPP

# include <iostream>

class Fixed {
    private:
        int					_raw;
        static const int	_frac = 8;

    public:
        Fixed();
        ~Fixed();
        Fixed(const Fixed& other);
        Fixed& operator=(const Fixed& other);

        int		getRawBits(void) const;
        void	setRawBits(int const raw);
};
#endif
