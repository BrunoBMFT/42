#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>
#include "Contact.hpp"

class PhoneBook {
	private:
		Contact *contacts;
		int index;
		int contactNum;
	public:
		PhoneBook();
		~PhoneBook();
		void AddContact(Contact);
		void Search();
};