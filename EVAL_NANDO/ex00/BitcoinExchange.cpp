#include "BitcoinExchange.hpp"


void BitcoinExchange::get_limit_date()
{
    time_t now = time(0);

    tm *current_time = localtime(&now);
    limit_year = 1900 + current_time->tm_year; 
    limit_month = 1 + current_time->tm_mon; 
    limit_day =  current_time->tm_mday;
}

/* 
    std::string yr;
    std::string mth;
    std::string dy;

    int limit_year;
    int limit_month;
    int limit_day;
 */

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other) 
: mapp(other.mapp), file_name(other.file_name), yr(other.yr), mth(other.mth), dy(other.dy), limit_year(other.limit_year), limit_month(other.limit_month), limit_day(other.limit_day)
{
    std::cout << "copy constructor called" << std::endl;
}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
    if (this != &other)
    {
        mapp = other.mapp;
        file_name =  other.file_name;
        yr =  other.yr;
        mth =  other.mth;
        dy =  other.dy;
        limit_day = other.limit_day;
        limit_month = other.limit_month;
        limit_year = other.limit_year;

    }
    std::cout << "operator overload called" << std::endl;
    return *this;
}


int BitcoinExchange::check_date_veracity(int y, int m,int d)
{ // 0 if not valid
    if (y < 0 || y > limit_year)
        return 0;
    if (m <= 0 || m > 12)
        return 0;
    if (d < 1)
        return 0;
    switch (m)
    {
        case 1:
        {
            if (d > 31)
                return 0;
            break;
        }
        case 2:
        {
            if ((y % 4 == 0 && y % 100 != 0) || y % 400 == 0) // leap year
            {
                if (d > 29)
                    return 0;
            }
            else //(dayd > 31)
                if (d > 28)
                    return 0;
            break;
        }
        case 3:
        {
            if (d > 31)
                return 0;
            break;
        }
        case 4: // april
        {
            if (d > 30)
                return 0;
            break;
        }
        case 5: // may
        {
            if (d > 31)
                return 0;
            break;
        }
        case 6: // june
        {
            if (d > 30)
                return 0;
            break;
        }
        case 7: // july
        {
            if (d > 31)
                return 0;
            break;
        }
        case 8: // august
        {
            if (d > 31)
                return 0;
            break;
        }
        case 9: // september
        {
            if (d > 30)
                return 0;
            break;
        }
        case 10: // october
        {
            if (d > 31)
                return 0;
            break;
        }
        case 11: // november
        {
            if (d > 30)
                return 0;
            break;
        }
        case 12: // december
        {
            if (d > 31)
                return 0;
            break;
        }
        default:
            return 0;
    }
    return 1;
}

int BitcoinExchange::parse_date(std::string date)
{
    std::string year; 
    std::string month; 
    std::string day;
    
    int flag = 0;
    for (size_t i = 0; i < date.size(); i++)
    {

        if (date[i] == '-' && flag == 0)
        {
            year = date.substr(0, i);
            flag++;
        }
        if(date[i] == '-' && flag == 1)
        {
            
            if (i < date.size())
            {
                size_t j = i;
                while(j > date.size() && date[j] != '-')
                    j++;
                j--;
                month = date.substr(i + 1, j - 1);
            flag++;
            }
        }
        if (date[i] == '-' && flag == 2)
        {
            day = date.substr(i + 1, date.size());
        }
    }
    if (!check_date_veracity(atoi(year.c_str()), atoi(month.c_str()), atoi(day.c_str())))
        return 0;
    return 1;
}

void BitcoinExchange::print_table(std::string date,double * quantity_nbr)
{
    double quantity_of_btc = *quantity_nbr;
    for(std::map<std::string, double>::iterator it = mapp.begin(); it != mapp.end(); it++ )
    {
        if (date > it->first)
            continue;
        else
        {
            std::cout << date << " => " << quantity_of_btc << " = " << it->second * (quantity_of_btc) << std::endl; 
            break;
        }
    }
}

int BitcoinExchange::parse_value(std::string raw_val, double *value_nbr)
{
    double i = 0;
    while(raw_val[i] && !isdigit(raw_val[i]))
    i++;
    raw_val = raw_val.substr(i, raw_val.size());
    for (size_t i = 0; i < raw_val.size(); i++)
    {
        if (!isdigit(raw_val[i]))
        return 0;
    }
    std::stringstream buffer(raw_val);
    if (buffer.fail())
    return 0;
    buffer >> *value_nbr;
    if (*value_nbr > (double)__INT_MAX__ || *value_nbr < 0 )
        return 0;
    
    return 1;
}

int parseHeader( std::string &line)
{
    std::string s;
    for (size_t i = 0; i < line.size(); i++)
    {
        if (line[i] != ' ')
            s += line[i];
    }
    if (s == "date|value")
        return 1;
    return 0;
}
void BitcoinExchange::check_doc()
{
    std::string buffer;
    std::string raw_val = "0";
    double bf;
    double *parsed_val = &bf;
    
    while (std::getline(this->read_f, buffer))
    {
        if (parseHeader(buffer) == 0)
            break;
    }
    while(std::getline(this->read_f, buffer))
    {
        int i = 0;
        while(buffer[i] && buffer[i] == ' ')
            i++;
        if (buffer[i] == '\n')
            continue;
        else
        {
            int j = i;
            while(buffer[j] && (isdigit(buffer[j]) || buffer[j] == '-'))
            j++;
            std::string date = buffer.substr(i, j);
            if (buffer.find('|') != std::string::npos && (buffer.size() - j >= 2))
            {
                raw_val = buffer.substr(j, buffer.size());
        }
        if (date.empty())
            continue;
        else if (!parse_date(date) || !parse_value(raw_val, parsed_val))
            std::cout << "non valid" << std::endl;
        else
            print_table(date, parsed_val);
        }
        }               
    
}

void BitcoinExchange::analise_doc(std::string file_name)
{
    read_f.open(file_name.c_str());
    if (!read_f.is_open())  
    {
        throw  std::runtime_error("open function failed!"); 
    }
    std::string f_line;
    std::getline(read_f, f_line);
    int i = 0;
    while (f_line[i] && std::isspace(f_line[i]))
        i++;
    f_line = f_line.substr(i, f_line.size());
    i = f_line.length() - 1 ;
    while (i >= 0 && std::isspace(f_line[i]))
    {
        std::cout << i;
        i--;
    }
    i++;
    f_line = f_line.substr(0, i);
    if (f_line.substr(0, 4) == "date")
    {
        f_line = f_line.substr(4, f_line.size());
        int i = 0;
        while(f_line[i] && std::isspace(f_line[i]))
            i++;
        if (f_line[i] != '|')
        {
            std::cout << RED << "ERROR(NOT PIPE): " << END <<  std::endl;
            return ;
        }
        i++;
        while(f_line[i] && std::isspace(f_line[i]))
            i++;
        f_line = f_line.substr(i, f_line.size());
        if (f_line != "value")
        {
            std::cout << RED << "ERROR(VALUE): " << END <<  std::endl;
            return ;
        }
        check_doc();
    }
}

BitcoinExchange::BitcoinExchange() 
{
    std::string buffer;
    std::cout << GREEN << "BitcoinExchange Constructor called!" <<END<<  std::endl;

    std::ifstream read_f;
    read_f.open("data.csv");
    if (!read_f.is_open())  
    {
        throw  std::runtime_error("open function failed!"); 
    }
    std::string date;
    std::string value;
    while(std::getline(read_f, buffer))
    {
        int i = 0;
        while(buffer[i] && buffer[i] != ',')
            i++;
        date = buffer.substr(0, i);
        value = buffer.substr(i + 1, buffer.size());
        mapp[date] = atof(value.c_str());
    }
    get_limit_date();
}


BitcoinExchange::~BitcoinExchange()
{
    std::cout << RED << "BitcoinExchange Destructor called!" <<END<<  std::endl;

}
