#ifndef VECT2_HPP
# define VECT2_HPP
# include <iostream>


class vect2
{
    private:
        int n0, n1;
    public:
        vect2() : n0(0), n1(0) {}
        vect2(int a, int b) : n0(a), n1(b) {}
        vect2(const vect2& other){n0 = other.n0; n1 = other.n1;}

		//overload for =
		vect2& operator=(const vect2& other) {
			n0 = other[0];
			n1 = other[1];
			return *this;
		}

		//overloads for []
		int operator[](int n) const {
			if (n == 0)
				return n0;
			return n1;
		}
		int& operator[](int n) {
			if (n == 0)
				return n0;
			return n1;
		}

		//++ and --
		vect2 operator++(int){
			vect2 copy(*this);
			n0++;
			n1++;
			return copy;
		}
		vect2& operator++(){
			n0++;
			n1++;
			return *this;
		}
		vect2 operator--(int){
			vect2 copy(*this);
			n0--;
			n1--;
			return copy;
		}
		vect2& operator--(){
			n0--;
			n1--;
			return *this;
		}


		// += and -=
		vect2 operator+=(const vect2& other){
			n0 += other[0];
			n1 += other[1];
			return *this;
		}
		vect2 operator-=(const vect2& other){
			n0 -= other[0];
			n1 -= other[1];
			return *this;
		}


		// + and - and *
		vect2 operator+(const vect2& a) const {
			vect2 temp(n0 + a[0], n1 + a[1]);
			return temp;
		}
		vect2 operator-(const vect2& a) const {
			vect2 temp(n0 - a[0], n1 - a[1]);
			return temp;
		}
		friend vect2 operator*(int n, const vect2& a) {
			vect2 temp(a[0] * n, a[1] * n);
			return temp;
		}
		// == and !=
		bool operator==(const vect2& other){
			if (n0 == other[0] && n1 == other[1])
				return true;
			return false;
		}
		bool operator!=(const vect2& other){
			if (n0 != other[0] && n1 != other[1])
				return true;
			return false;
		}

};
	
std::ostream& operator<<(std::ostream& o, const vect2& v) {
	o << "{" << v[0] << ", " << v[1] << "}";
	return o;
}





#endif