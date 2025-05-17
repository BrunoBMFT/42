#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <iomanip>

class Contact {
	private:
		std::string first, last, nick, phone, secret;

	public:
		Contact() {}
		~Contact() {}
		void set_values(std::string, std::string, std::string, std::string, std::string);
		bool Add_info(Contact *contact);
		void print_Small_Info(int i);
		void print_Info();
};