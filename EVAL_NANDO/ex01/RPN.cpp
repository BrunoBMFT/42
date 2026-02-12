#include "RPN.hpp"

RPN::RPN(const RPN &other) : c(other.c), str(other.str)
{
    std::cout << "copy constructor called" << std::endl;
}

RPN &RPN::operator=(const RPN & other)
{
    if (this != &other)
    {
        c = other.c;
        str = other.str;
    }
    return *this;
}



int RPN::check_input(std::string str)
{
    std::string operators = "*+-/";
 
    for (size_t i = 0; i <  str.length() ; i++)
    {
        if (str[i] == ' ')
            continue;
        else  if (operators.find(str[i]) == std::string::npos && !isdigit(str[i]))
            return 0;
    }
    return 1;
}

RPN::RPN(std::string _str) : str(_str)
{
    std::cout << "RPN constructor called!" << std::endl;

    if (!check_input(str) || str.empty())
    {
        std::cerr << "Error" << std::endl;
        return ;
    }
    execute_RPN();
}

void RPN::sum_operator()
{
    int x,y, result;

    if (c.empty())
        return ;
    x = c.top();
    c.pop();
    if (c.empty())
        return ;
    y = c.top();
    c.pop();
    result = y + x;
    c.push(result);
}

void RPN::res_operator()
{
    int x,y, result;
    if (c.empty())
        return ;
    x = c.top();
    c.pop();
    if (c.empty())
        return ;
    y = c.top();
    c.pop();
    result = y - x;
    c.push(result);
}

void RPN::mult_operator()
{
    int x,y, result;
    if (c.empty())
        return ;
    x = c.top();
    c.pop();
    if (c.empty())
        return ;
    y = c.top();
    c.pop();
    result = y * x;
    c.push(result);
}

void RPN::div_operator()
{
    int x,y, result;
    if (c.empty())
        return ;
    x = c.top();
    c.pop();
    if (c.empty())
        return ;
    y = c.top();
    c.pop();
    result = y / x;
    c.push(result);
}

void RPN::calculate(char op)
{
    switch (op)
    {
    case '+':
        sum_operator();
        break;
    case '-':
        res_operator();
        break;
    case '*':
        mult_operator();
        break;
    case '/':
        div_operator();
        break;
    default:
        std::cerr << "error:" << std::endl;
        break;
    }
}

void RPN::execute_RPN(){

    for (size_t i = 0; i < str.length(); i++)
    {
        if (str[i] == ' ')
            continue;
        else if (isdigit(str[i]))
        {
            int nbr = str[i] - '0';
            c.push(nbr);
        }
        else
            calculate(str[i]);
    }
    if (c.empty())
        std::cerr << "Error" << std::endl;
    else
        std::cout << "result: " << c.top() << std::endl;
}   



RPN::~RPN()
{
    std::cout << "RPN destructor called!" << std::endl;
}
