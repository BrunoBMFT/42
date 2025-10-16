#include "../includes/Base.hpp"
#include "../includes/A.hpp"
#include "../includes/B.hpp"
#include "../includes/C.hpp"

Base* generate(void){
	int r = rand() % 3;
	switch (r) {
		case 0:
			return new A;
		case 1:
			return new B;
		case 2:
			return new C;
	}
	return NULL;
}

void identify(Base* p){
	std::cout << "Using Base* p:\t";
	if (dynamic_cast<A*>(p))
		std::cout << "A\n";
	else if (dynamic_cast<B*>(p))
		std::cout << "B\n";
	else if (dynamic_cast<C*>(p))
		std::cout << "C\n";
	else 
		std::cout << "Unknown\n";
}

void identify(Base& p){
	std::cout << "Using Base& p:\t";
	try{
		A &a = dynamic_cast<A&>(p);
		std::cout << "A\n";
		(void)a;
		return ;
	} catch (std::exception &e) {}
	try{
		B &b = dynamic_cast<B&>(p);
		std::cout << "B\n";
		(void)b;
		return ;
	} catch (std::exception &e) {}
	try{
		C &c = dynamic_cast<C&>(p);
		std::cout << "C\n";
		(void)c;
		return ;
	} catch (std::exception &e) {}
		std::cout << "Unknown\n";
}

int main() {
	srand(time(NULL));

	Base *ptr = generate();
	Base &ref = *ptr;
	identify(ptr);
	identify(ref);
	delete ptr;


	return 0;
}