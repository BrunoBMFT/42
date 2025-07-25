#ifndef BIGINT_HPP
# define BIGINT_HPP
# include <string>
# include <iostream>
# include <algorithm>

class bigint
{
    private:
        std::string num;
    public:
        bigint() : num("0");
        bigint(size_t n) : num(std::to_string(n)) {}
        bigint(const bigint& oth) num(oth.num) {}
        bigint(const std::string& n){
            if (n.empty() || !std::all_of(n.begin(), n.end(), ::isdigit) || \
            (n.size() > 1 && n[0] == '0')){
                std::cout << "INvalid number string" << std::endl;
                num = "0";
            }
            else
                num = n;
        }
        friend std::ostream& operator<<(std::ostream& o, const bigint& b){
            return o << b.num;
        }
        std::string add_strings(const std::string& n1, const std::string& n2) const {
            std::string result;
            int carry = 0, i = n1.size() - 1, j = n2.size() - 1;
            while (i >= 0 || j >= 0 || carry){
                int sum = (i >= 0 ? n1[i--] - '0' : 0) + (j >= 0 ? n2[j--] - '0' : 0) + carry;
                result.
            }
        }
};

#endif