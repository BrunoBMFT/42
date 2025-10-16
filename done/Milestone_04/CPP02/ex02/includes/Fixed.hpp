#ifndef Fixed_HPP
# define Fixed_HPP

# include <iostream>

class Fixed {
    private:
        int                 _raw;
        static const int    _frac = 8;

    public:
        Fixed();
        Fixed(const int);
        Fixed(const float);
        ~Fixed();
        Fixed(const Fixed& other);
        Fixed& operator=(const Fixed& other);
        
        int			getRawBits(void) const;
        void		setRawBits(int const raw);
        float		toFloat(void) const;
        int			toInt(void) const;
        
        bool		operator>(Fixed const &other) const;
        bool		operator<(Fixed const &other) const;
        bool		operator>=(Fixed const &other) const;
        bool		operator<=(Fixed const &other) const;
        bool		operator==(Fixed const &other) const;
        bool		operator!=(Fixed const &other) const;

        Fixed		operator+(Fixed const &other) const;
        Fixed		operator-(Fixed const &other) const;
        Fixed		operator*(Fixed const &other) const;
        Fixed		operator/(Fixed const &other) const;
        
        Fixed&		operator++();
        Fixed		operator++(int);
        Fixed&		operator--();
        Fixed		operator--(int);

		static Fixed&	min(Fixed &f1, Fixed &f2);
		static Fixed	min(Fixed const &f1, Fixed const &f2);
		static Fixed&	max(Fixed &f1, Fixed &f2);
		static Fixed	max(Fixed const &f1, Fixed const &f2);
};

std::ostream&	operator<<(std::ostream &o, Fixed const &fixed);


#endif
