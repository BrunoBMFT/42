    #pragma once

#include <string>
#include <string.h>
#include <cstring>
#include <cctype>
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <fstream>
#include <vector>
#include <unistd.h>
#include <iterator>
#include <sstream>
#include <cerrno>     // For errno
#include <map>

#define RED "\033[31m"
#define GREEN "\033[32m"
#define YELLOW "\033[33m" 
#define BLUE  "\033[34m"
#define OLIVE "\033[38;5;3m"
#define PURPLE "\033[38;5;5m"
#define ORANGE "\033[38;5;208m"
#define CYAN "\033[38;5;6m"
#define LIGHT_GRAY "\033[38;5;7m"
#define DARK_GRAY "\033[38;5;8m"
#define END  "\033[0m"

 class BitcoinExchange
{
private:
    std::map< std::string, double> mapp;
    std::string file_name;
    std::ifstream read_f;

    std::string yr;
    std::string mth;
    std::string dy;

    int limit_year;
    int limit_month;
    int limit_day;
    
public:
    BitcoinExchange(); // default will fill the database with the data.cvs info
    BitcoinExchange(const BitcoinExchange &other); // default will fill the database with the data.cvs info
    BitcoinExchange& operator=(const BitcoinExchange &other); // default will fill the database with the data.cvs info
    void analise_doc(std::string file_name); // will verify and read input.txt
    void check_doc(/* std::ifstream read_f */);
    void print_table(std::string date,double * quantity_nbr);
    int check_date_veracity(int y, int m,int d);

    void get_limit_date();
    int parse_date(std::string date/* ,std::string val */);
    int parse_value(std::string raw_val, double *value_nbr);
    //BitcoinExchange(std::string _file_name);

    ~BitcoinExchange();
};
