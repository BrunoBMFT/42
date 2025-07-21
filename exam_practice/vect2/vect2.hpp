#ifndef VECT2_HPP
# define VECT2_HPP
# include <iostream>

class vect2
{
    private:
        int n1, n2;
    public:
        vect2() : n1(0), n2(0) {}
        vect2(int num1, int num2) : n1(num1), n2(num2) {}
        vect2(const vect2& ori) : n1(ori.n1), n2(ori.n2) {}
        vect2& operator=(const vect2& ori) {
            // if (*this != ori){
                n1 = ori.n1;
                n2 = ori.n2;
            // }
            return (*this);
        }

        // int& operator[](int i) {return(i == 0 ? n1:n2);}//might not be needed?
        int operator[](int i) const {return(i == 0 ? n1:n2);}
        ~vect2() {}



        vect2 operator+(const vect2& other) const {
            return (vect2(n1 + other[0], n2 + other[1]));
        }
        vect2 operator*(int s, const vect2& other) {
            return (vect2(other[0] * s, other[1] * s));
        }



        vect2 operator+=(const vect2& other){
            n1 += other[0];
            n2 += other[1];
            return (*this);
        }
        vect2 operator-=(const vect2& other){
            n1 -= other[0];
            n2 -= other[1];
            return (*this);
        }
        //increment decrement
        vect2 operator++(int){
            vect2 copy(*this);
            n1++;
            n2++;
            return (copy);
        }
        vect2& operator++(){
            n1++;
            n2++;
            return (*this);
        }
        vect2 operator--(int){
            vect2 copy(*this);
            n1--;
            n2--;
            return (copy);
        }
        vect2& operator--(){
            n1--;
            n2--;
            return (*this);
        }




        //equal to
        bool operator==(const vect2& other){
            if (n1 == other[0] && n2 == other[1])
                return true;
            return false;
        }
        bool operator!=(const vect2& other){
            if (n1 != other[0] && n2 != other[1])
                return true;
            return false;
        }

};

std::ostream& operator<<(std::ostream& out, const vect2& v){
    out << "{" << v[0] << ", " << v[1] << "}";
    return out;
}


#endif