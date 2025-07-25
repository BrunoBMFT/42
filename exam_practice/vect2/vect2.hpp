#ifndef VECT2_HPP
# define VECT2_HPP
# include <iostream>

class vect2
{
	private:
		int n0, n1;
	public:
		vect2() : n0(0), n1(0) {}
		vect2(int num0, int num1) : n0(num0), n1(num1) {}
		vect2(const vect2& oth) : n0(oth[0]), n1(oth[1]) {}

		vect2& operator=(const vect2& oth){
			n0 = oth[0];
			n1 = oth[1];
			return *this;
		}

		int operator[](int i) const { if (i == 0) return n0; return n1; }
		int& operator[](int i) { if (i == 0) return n0; return n1; }

		friend std::ostream& operator<<(std::ostream& o, const vect2& v){
			o << "{" << v[0] << ", " << v[1] << "}";
			return o;
		}

		vect2 operator++(int){
			vect2 tmp(*this);
			n0++;
			n1++;
			return tmp;
		}
		vect2& operator++(){
			n0++;
			n1++;
			return *this;
		}
		vect2 operator--(int){
			vect2 tmp(*this);
			n0--;
			n1--;
			return tmp;
		}
		vect2& operator--(){
			n0--;
			n1--;
			return *this;
		}

		vect2 operator+=(const vect2& oth){
			n0 += oth[0];
			n1 += oth[1];
			return *this;
		}
		vect2 operator-=(const vect2& oth){
			n0 -= oth[0];
			n1 -= oth[1];
			return *this;
		}

		vect2 operator+(const vect2& oth) const {
			return vect2(n0 + oth[0], n1 + oth[1]);
		}
		vect2 operator-(const vect2& oth) const {
			return vect2(n0 - oth[0], n1 - oth[1]);
		}
		vect2 operator*(const vect2& oth) const {
			return vect2(n0 * oth[0], n1 * oth[1]);
		}
		friend vect2 operator*(int i, const vect2& oth) {
			return vect2(i * oth[0], i * oth[1]);
		}

		bool operator==(const vect2& oth){
			return (n0 == oth[0] && n1 == oth[1]);
		}

		bool operator!=(const vect2& oth){
			return !(n0 == oth[0] && n1 == oth[1]);
		}


};

#endif