#ifndef FORM_HPP
# define FORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class Form {
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_toSign;
		const int			_toExec;
	public:
		Form();
		Form(std::string name, const int toSign, const int toExec);
		Form(const Form &other);
		Form &operator=(const Form &other);
		~Form();

		std::string	getName() const;
		bool		getIsSigned() const;
		int			getToSign() const;
		int			getToExec() const;
		
		void		beSigned(const Bureaucrat &bureau);

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream &o, Form const &form);

#endif
