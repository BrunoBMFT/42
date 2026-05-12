#ifndef AFORM_HPP
# define AFORM_HPP

# include <iostream>
# include "Bureaucrat.hpp"

class Bureaucrat;

class AForm {
	private:
		const std::string	_name;
		bool				_isSigned;
		const int			_toSign;
		const int			_toExec;

	public:
		AForm();
		AForm(std::string name, const int toSign, const int toExec);
		AForm(const AForm &other);
		AForm &operator=(const AForm &other);
		virtual ~AForm();

		std::string		getName() const;
		bool			getIsSigned() const;
		int				getToSign() const;
		int				getToExec() const;

		void			beSigned(const Bureaucrat &bureau);
		void			execute(const Bureaucrat &bureau);
		virtual	void	doAction() const = 0;

		class GradeTooHighException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class GradeTooLowException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
		class NotSignedException : public std::exception {
			public:
				virtual const char* what() const throw();
		};
};

std::ostream&	operator<<(std::ostream &o, AForm const &form);

#endif
