#include "PmergeMe.hpp"
#include<unistd.h>
#include <stdio.h>
PmergeMe::vtr jn_v(int n)
{
    PmergeMe::vtr jn; 
    jn.push_back(0);
    jn.push_back(1);

    for (int i = 2; i <= n; i++)
    {
        int j1 = jn[i - 1];
        int j2 = jn[i - 2];
        jn.push_back(j1 + (2 * j2));
        if (jn[i] > n)
        {
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.pop_back();
            return jn;
        }
    }
    jn.erase(jn.begin());
    jn.erase(jn.begin());
    return jn;
}

PmergeMe::dq jn_d(int n)
{
    PmergeMe::dq jn; 
    jn.push_back(0);
    jn.push_back(1);

    for (int i = 2; i <= n; i++)
    {
        int j1 = jn[i - 1];
        int j2 = jn[i - 2];
        jn.push_back(j1 + (2 * j2));
        if (jn[i] > n)
        {
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.erase(jn.begin());
            jn.pop_back();
            return jn;
        }
    }
    jn.erase(jn.begin());
    jn.erase(jn.begin());
    jn.erase(jn.begin());
    return jn;
}

bool check_numbers(std::vector<int> &s)
{
    if (s.size() < 2)
        return true;
    for (std::vector<int>::const_iterator it = s.begin(); it != s.end() - 1; it++)
    {
        if (*it > *(it + 1))
            return false;
    }
    return true;
}


bool check_numbers(std::deque<int> &s)
{
    if (s.size() < 2)
        return true;
    for (std::deque<int>::const_iterator it = s.begin(); it != s.end() - 1; it++)
    {
        if (*it > *(it + 1))
            return false;
    }
    return true;
}

int check_string(std::string str)
{
    if (str.empty())
        throw std::runtime_error("empty string");
    for (size_t i = 0; i < str.size(); i++)
    {
        if (str[i] != ' ' && !isdigit(str[i]))
            throw std::runtime_error("non valid str");
    }
    return 1;
}


void PmergeMe::tester()
{
    int size = rand() %  3000 + 1; // change 10 to make the sequence bigger
    
    vtr test1;
    dq test2;
    for (int i = 0; i < size; i++)
        test1.push_back(std::rand() % size + 1);
    this->vt = test1;    
    std::cout << "BEFORE: " ;
    pv(vt);    
    merge_insert(this->vt, 2);
    std::cout << GREEN << "AFTER: " ;
    pv(vt)  ;    

    if (check_numbers(this->vt))
        std::cout  << GREEN << "|test|"<< RED << "|result|: "<< END <<" 🇵🇹 🦅\n========================================" << std::endl;
    else
        std::cout << OLIVE << "!!!! WRONG!!!!\n" << std::endl;

    dq deq;
    for (int i = 0; i < size; i++)
        test2.push_back(std::rand() % size + 1);
    this->dque = test2;
    pv(vt);
    printf("\t\t\tIIIIII\n");
    merge_insert(this->dque, 2);
    std::cout << GREEN << "AFTER: " ;
    pv(vt)  ;    

    if (check_numbers(this->dque))
        std::cout  << GREEN << "|test|"<< RED << "|result|: "<< END <<" 🇵🇹 🦅\n========================================" << std::endl;
    else
        std::cout << OLIVE << "!!!! WRONG!!!!\n" << std::endl;

        
}


std::string convert(int ac, char **av)
{
    std::string result;
    for (int i = 0; i < ac - 1; ++i)
    {
        result += av[i];
        if (i != ac - 1)
            result += " ";
    }
    return result;

}

PmergeMe::PmergeMe(const PmergeMe &other) : vt(other.vt), dque(other.dque)
{
    std::cout << "copy constructor called!" << std::endl;
}


PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        vt = other.vt;
        dque = other.dque;
    }
    std::cout << "operator overload called!" << std::endl;
    return *this;
}


PmergeMe::PmergeMe(int ac, char **av)
{
    if (TEST)
    {
        tester();
        return ;
    }
        std::string str;
        gettimeofday(&vt_start, NULL);
        str = convert(ac, av);
        check_string(str);
        fill_vt(str);
        std::cout << "BEFORE: ";
        pv(this->vt);
        if (!check_numbers(this->vt)) // not sorted
            merge_insert(this->vt, 2);    
        gettimeofday(&vt_end, NULL);
        
        
        gettimeofday(&dq_start, NULL);
        str = convert(ac, av);
        check_string(str);  
        fill_dq(str); 
        if (!check_numbers(this->dque)) // not sorted
            merge_insert(this->dque, 2);    
        gettimeofday(&dq_end, NULL);

        std::cout << std::endl;


    std::cout << "AFTER : ";
    pv(this->dque);
    
    std::cout << "Time to process a range of " << this->vt.size() << " elements with std::vector : ";
    long vt_sec = dq_end.tv_sec - dq_start.tv_sec;
    long vt_usec = dq_end.tv_usec  - dq_start.tv_usec;
    if (vt_usec < 0)
    {
        vt_usec += 1000000;
        vt_sec -= 1;
    }
    printf("%ld.%06ld us\n",vt_sec ,vt_usec );

    std::cout << "Time to process a range of " << dque.size() << " elements with std::deque : ";
    long dq_sec = dq_end.tv_sec - dq_start.tv_sec;
    long dq_usec = dq_end.tv_usec  - dq_start.tv_usec;
    if (dq_usec < 0)
    {
        dq_usec += 1000000;
        dq_sec -= 1;
    }
    printf("%ld.%06ld us\n",dq_sec ,dq_usec );

   

}

void PmergeMe::pv(PmergeMe::dq a/* , std::string color */)
{
    for (PmergeMe::dq_it it = a.begin(); it != a.end() ; it++)
        std::cout << *it << " ";
    std::cout << std::endl;
    }


void PmergeMe::pv(PmergeMe::vtr a)
{
    for (PmergeMe::vtr_it it = a.begin(); it != a.end() ; it++)
        std::cout<< *it << " ";
    std::cout << std::endl;
}

void PmergeMe::fill_vt(std::string str) {
    PmergeMe::vtr tk_vt;
    this->vt = split(str, tk_vt);
}

void PmergeMe::fill_dq(std::string str) {
    PmergeMe::dq tk_dq;
    this->dque = split(str, tk_dq);
}

PmergeMe::vtr PmergeMe::split(const std::string &str, PmergeMe::vtr token_vector)
{
	std::string 		 token;
	std::istringstream 	 iss(str);

    int x = 0;
	while(iss >> token)
    {
        x = atoi(token.c_str());
        if (x == -1)
            throw std::runtime_error("overflow of the interger value!");;
        token_vector.push_back(x);
    }
	return token_vector;
}

PmergeMe::dq PmergeMe::split(const std::string &str, PmergeMe::dq token_dq)
{
	std::string 		 token;
	std::istringstream 	 iss(str);

    int x = 0;
	while(iss >> token)
    {
        x = atoi(token.c_str());
        if (x == -1)
            throw std::runtime_error("overflow of the interger value!");;
        token_dq.push_back(x);
    }
	return token_dq;
}

int find_main_x(std::vector<std::string> v,  std::string pend_insert)
{
    pend_insert.erase(pend_insert.begin());
    int bx = atoi(pend_insert.c_str());
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string tmp = *it;
        tmp.erase(tmp.begin());
        int b_num = atoi(tmp.c_str());
        if (b_num == bx)
            return std::distance(v.begin(), it);
    }
    return v.size() - 1; 
}

int find_main_x(std::deque<std::string> v,  std::string pend_insert)
{
    pend_insert.erase(pend_insert.begin());
    int bx = atoi(pend_insert.c_str());
    for (std::deque<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string tmp = *it;
        tmp.erase(tmp.begin());
        int b_num = atoi(tmp.c_str());
        if (b_num == bx)
            return std::distance(v.begin(), it);
    }
    return v.size() - 1; 
}

int find_pend_x(std::vector<std::string> &v,  int x)
{// x e o numero de jac que vamos procurar no pend para mandar para o main
    int tmp = 0;
    std::vector<std::string>::iterator max  = v.begin();
    
    for (std::vector<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string s = *it;
        s.erase(s.begin()); 
        if (atoi(s.c_str()) >= tmp && atoi(s.c_str()) <= x)
        {
            tmp = atoi(s.c_str());
            max = it;
        }
        else
            break;
    }
    tmp = std::distance(v.begin(), max);
    return tmp;
}

int find_pend_x(std::deque<std::string> &v,  int x)
{// x e o numero de jac que vamos procurar no pend para mandar para o main
    int tmp = 0;
    std::deque<std::string>::iterator max  = v.begin();
   // std::cout << x << std::endl;
    
    for (std::deque<std::string>::iterator it = v.begin(); it != v.end(); it++)
    {
        std::string s = *it;
        s.erase(s.begin()); 
        if (atoi(s.c_str()) >= tmp && atoi(s.c_str()) <= x)
        {
            tmp = atoi(s.c_str());
            max = it;
        }
        else
            break;
    }
    tmp = std::distance(v.begin(), max);
    return tmp;
}


int upgrade_jn(std::vector<std::string> pend_str, int jac_number )
{
    std::string str = pend_str[0];
    str.erase(str.begin());
    int r  = atoi(str.c_str()) ;
    if ((r > jac_number))
        return 1;
    return 0;
}

int upgrade_jn(std::deque<std::string> pend_str, int jac_number )
{
    std::string str = pend_str[0];
    str.erase(str.begin());
    int r  = atoi(str.c_str()) ;
    if ((r > jac_number))
        return 1;
    return 0;
}


void PmergeMe::merge_insert(PmergeMe::vtr &head_vectors, int cel_size)
{
    /*  na iteracao para checar cada numero , eu tenho que criar blocos de numeros que irao ser denominados por
    // para saber o numero de blocks (A/B)x -> block_ n = head_vectors.size() / (celsize/2);
    (a / b)x para calcular o numero de blockos que podem sair do veotr inicial, eu
        numero_de_blocos = head_vectors.size() / (cel_size/2)
        no loop para criar CADA a e b x, terei um contador que sera incremetnado a cada ACAO de (acao == criar um bloco ax ou bx) quando chegar ao 
        maximo de blocos possiveis de criar, e se ainda tiver numeros para tal, entao esses serao nao participantes
        e serao adicionados no final do head_vectors
        // tenho que parar de checar por pares quando i > block_n; 
        */
    PmergeMe::vector_pair cels;
    PmergeMe::vtr head_cels;
    PmergeMe::vtr vector_sorted = this->vt;
    int index = 0;
    int max_blocks =  this->vt.size() / (cel_size/2);
    int i = 0;
    for (PmergeMe::vtr_it it = head_vectors.begin(); it != head_vectors.end();) 
    {
        
        if (i < max_blocks)
        {
            PmergeMe::vtr_it tmp;
            if ((it + 1 != head_vectors.end()))
            {
                tmp = it + 1;
                if (*tmp < *it)
                {
                    if (cel_size == 2)
                        std::swap(vector_sorted[index], vector_sorted[(index + 1)]);
                    else
                    {
                        for (int i = 0; i < (cel_size/2); i++)
                            std::swap(vector_sorted[((index*(cel_size/2))) + i], vector_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                    }
                    head_cels.push_back(*it); 
                }
                else
                    head_cels.push_back(*tmp);
                index +=2;
                it+=2;
                //pv(head_cels, ORANGE, 0);
                
            }
            i++;
        }
        else
            break;
    }
    this->vt = vector_sorted;
    if ((cel_size <= (int)this->vt.size()/2))
        merge_insert(head_cels, cel_size * 2);
    vtr pend;
    vtr main;
    index = 0;
  std::vector<std::string> main_str;
  std::vector<std::string> pend_str;
  int increment = 0;

  for (vtr_it it = this->vt.begin(); it != this->vt.end() ;)
  {
    if(increment >= max_blocks)
    {
        if ((int)this->vt.size() > (max_blocks * cel_size / 2))
        {
            int index2 = max_blocks * cel_size / 2;
            while ((int)this->vt.size() > index2)
                pend.push_back(this->vt[index2++]);
            break;
        }
    }
      if (index % 2 == 0) // Bx
      {
          if (index == 0)
          {
                for (int i = 0; i < cel_size/2; i++)
                    main.push_back(this->vt[index*(cel_size/2) + i]);
          }
          else
          {
            for (int i = 0; i < cel_size/2; i++)
            {
                if ((index*(cel_size/2) + i) >= (int)this->vt.size())
                    break;
                pend.push_back(this->vt[index*(cel_size/2) + i]); 
            }
          }
            increment++;
        }
        else // Ax
        {
            for (int i = 0; i < cel_size/2; i++)
            {
                if ((index*(cel_size/2) + i) >= (int)this->vt.size())
                    break;
                main.push_back(this->vt[index*(cel_size/2) + i]);
            }
            increment++;
        }        
        index++;
        it += (cel_size / 2);
    }
    
    int x_val = 1;
    for (size_t i = 0; i < main.size(); i += (cel_size / 2))
    {
        std::string b = "b";
        std::string a = "a";
        std::stringstream ss;
        if (i == 0)
        {
            ss << b << x_val;
            main_str.push_back(ss.str());
        }
        else
        {
            ss << a << x_val;
            main_str.push_back(ss.str());
            x_val++;
        }
    }
    x_val = 2;
    for (size_t i = 0; i < pend.size(); i += (cel_size / 2))
    {
        if (pend.size() - i < (unsigned long)cel_size/2)
            break;
        std::string b = "b";
        std::stringstream ss;
        ss << b << x_val;
        pend_str.push_back(ss.str());
        x_val++;
    }
    int number_blocks = this->vt.size() / (cel_size/2);
    bool alone = false;
    if (number_blocks % 2 == 1)
        alone = true;
    int bx = number_blocks / 2 + alone;
    
    vtr jn_vtr = jn_v(bx); // bx flag aponta para 3, e vamos encontrar o bx menor mais proximo dele.
    int h = 0; // h =  o index do jc vector do qual vamos aplicar no pend (na insercao)
    while(!pend.empty())
    {
        if (pend_str.empty())
        {
            // -> 
            for (size_t i = 0; i < pend.size(); i++)
                main.push_back(pend[i]);
            break;
        }
        if (upgrade_jn(pend_str,jn_vtr[h]))
            h++;        
        int pend_idx = find_pend_x(pend_str,jn_vtr.size() >= (unsigned long)h ?  jn_vtr[h] : bx );  //! -> VOU USAR ESTE INDEX PAR NO PEND ORIGINAL 

        std::string pend_string = pend_str[pend_idx]; // ! -> representa o pend cel que vamos inserir no main 

        int main_idx = find_main_x(main_str, pend_string); //! -> VOU USAR ESTE INDEX PAR NO MAIN ORIGINAL -> este e o index da celula correspondente ao pend_str
        int pend_target_start_idx = pend_idx*(cel_size/2); // 
        int pend_target_end_idx = (pend_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
       // int main_target_start_idx = main_idx*(cel_size/2); // 
        int main_target_end_idx = (main_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
        int  i = 0;
        while ((main_target_end_idx - ((cel_size/2) * i) >= 0) && (pend[pend_target_end_idx] <= main[main_target_end_idx - ((cel_size/2) * i) ]))
            i++;

        int ideal_main_insertion_idx = main_target_end_idx - ((cel_size/2) * i);
        int ideal_main_str_insertion_idx = ideal_main_insertion_idx / (cel_size/2);   //main_target_end_idx / (cel_size/2);

        for (int i = (cel_size/2); i > 0 ; i--) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            vtr_it it = main.begin() + (ideal_main_insertion_idx + 1);
            main.insert(it, pend[pend_target_end_idx - (cel_size/2) + i]);
        }
        main_str.insert(main_str.begin() + (ideal_main_str_insertion_idx + 1) , pend_string);
        for (int i = 0; i < (cel_size/2) ; i++) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            if (pend.empty())
                break;
            vtr_it it = pend.begin() + pend_target_start_idx;
            pend.erase(it);
        }
        pend_str.erase(pend_str.begin() + pend_idx);
    }    
    this->vt = main;    
}




void PmergeMe::merge_insert(PmergeMe::dq &head_dq, int cel_size)
{
    /*  na iteracao para checar cad numero , eu tenho que criar blocos de numeros que irao ser denominados por
    // para saber o numero de blocks (A/B)x -> block_ n = head_vectors.size() / (celsize/2);
    (a / b)x para calcular o numero de blockos que podem sair do veotr inicial, eu
        numero_de_blocos = head_vectors.size() / (cel_size/2)
        no loop para criar CADA a e b x, terei um contador que sera incremetnado a cada ACAO de (acao == criar um bloco ax ou bx) quando chegar ao 
        maximo de blocos possiveis de criar, e se ainda tiver numeros para tal, entao esses serao nao participantes
        e serao adicionados no final do head_vectors
        // tenho que parar de checar por pares quando i > block_n; 
        */
    PmergeMe::dq_pair cels;
    PmergeMe::dq head_cels;
    PmergeMe::dq dq_sorted = this->dque;
    int index = 0;
    int max_blocks =  this->dque.size() / (cel_size/2);
    int i = 0;
    for (PmergeMe::dq_it it = head_dq.begin(); it != head_dq.end();) 
    {
        
        if (i < max_blocks)
        {
            PmergeMe::dq_it tmp;
            if ((it + 1 != head_dq.end()))
            {
                tmp = it + 1;
                if (*tmp < *it)
                {
                    if (cel_size == 2)
                        std::swap(dq_sorted[index], dq_sorted[(index + 1)]);
                    else
                    {
                        for (int i = 0; i < (cel_size/2); i++)
                            std::swap(dq_sorted[((index*(cel_size/2))) + i], dq_sorted[((index*(cel_size/2)) + (cel_size/2) + i)]);
                    }
                    head_cels.push_back(*it); 
                }
                else
                    head_cels.push_back(*tmp);
                index +=2;
                it+=2;
            }
            i++;
        }
        else
            break;
    }
    this->dque = dq_sorted;
    if (((unsigned long)cel_size <= this->dque.size()/2))
    {
        merge_insert(head_cels, cel_size * 2);
    }
  dq pend;
  dq main;
  index = 0;
  std::deque<std::string> main_str;
  std::deque<std::string> pend_str;
  int increment = 0;

  for (dq_it it = this->dque.begin(); it != this->dque.end() ;)
  {
    if(increment >= max_blocks)
    {
        if (this->dque.size() > (unsigned long)(max_blocks * cel_size / 2))
        {
            int index2 = max_blocks * cel_size / 2;
            while (this->dque.size() > (unsigned long)index2)
                pend.push_back(this->dque[index2++]);
            break;
        }
    }
      if (index % 2 == 0) // Bx
      {
          if (index == 0)
          {
                for (int i = 0; i < cel_size/2; i++)
                    main.push_back(this->dque[index*(cel_size/2) + i]);
          }
          else
          {
            for (int i = 0; i < cel_size/2; i++)
            {
                if ((unsigned long )(index*(cel_size/2) + i) >= this->dque.size())
                    break;
                pend.push_back(this->dque[index*(cel_size/2) + i]); 
            }
          }
            increment++;
        }
        else // Ax
        {
            for (int i = 0; i < cel_size/2; i++)
            {
                if ((unsigned long)(index*(cel_size/2) + i) >= this->dque.size())
                    break;
                main.push_back(this->dque[index*(cel_size/2) + i]);
            }
            increment++;
        }        
        index++;
        it += (cel_size / 2);
    }
    
    int x_val = 1;
    for (size_t i = 0; i < main.size(); i += (cel_size / 2))
    {
        std::string b = "b";
        std::string a = "a";
        std::stringstream ss;
        if (i == 0)
        {
            ss << b << x_val;
            main_str.push_back(ss.str());
        }
        else
        {
            ss << a << x_val;
            main_str.push_back(ss.str());
            x_val++;
        }
    }
    x_val = 2;
    for (size_t i = 0; i < pend.size(); i += (cel_size / 2))
    {
        if ((pend.size() - i) < (unsigned long)cel_size/2)
            break;
        std::string b = "b";
        std::stringstream ss;
        ss << b << x_val;
        pend_str.push_back(ss.str());
        x_val++;
    }
    int number_blocks = this->dque.size() / (cel_size/2);
    bool alone = false;
    if (number_blocks % 2 == 1)
        alone = true;
    int bx = number_blocks / 2 + alone;
    
    dq jn_vtr = jn_d(bx); // bx flag aponta para 3, e vamos encontrar o bx menor mais proximo dele.
    int h = 0; // h =  o index do jc vector do qual vamos aplicar no pend (na insercao)
    //exit(1);
    while(!pend.empty())
    {
        if (pend_str.empty())
        {
            // -> 
            for (size_t i = 0; i < pend.size(); i++)
                main.push_back(pend[i]);
            break;
        }
        if (upgrade_jn(pend_str,jn_vtr[h] ))
            h++;        
        
        int pend_idx = find_pend_x(pend_str,jn_vtr.size() >= (unsigned long)h ?  jn_vtr[h] : bx );  //! -> VOU USAR ESTE INDEX PAR NO PEND ORIGINAL 

        std::string pend_string = pend_str[pend_idx]; // ! -> representa o pend cel que vamos inserir no main 

        int main_idx = find_main_x(main_str, pend_string); //! -> VOU USAR ESTE INDEX PAR NO MAIN ORIGINAL -> este e o index da celula correspondente ao pend_str
        int pend_target_start_idx = pend_idx*(cel_size/2); // 
        int pend_target_end_idx = (pend_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
        //int main_target_start_idx = main_idx*(cel_size/2); // 
        int main_target_end_idx = (main_idx*(cel_size/2) ) + ((cel_size/2) - 1); // 
        int  i = 0;
        while ((main_target_end_idx - ((cel_size/2) * i) >= 0) &&pend[pend_target_end_idx] <= main[main_target_end_idx - ((cel_size/2) * i) ])
            i++;


        int ideal_main_insertion_idx = 0;
        ideal_main_insertion_idx = main_target_end_idx - ((cel_size/2) * i);
        int ideal_main_str_insertion_idx = ideal_main_insertion_idx / (cel_size/2);   //main_target_end_idx / (cel_size/2);

        for (int i = (cel_size/2); i > 0 ; i--) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            dq_it it  =  main.begin()  + (ideal_main_insertion_idx + 1);
            main.insert(it, pend[pend_target_end_idx - (cel_size/2) + i]);
        }
        main_str.insert(main_str.begin() + (ideal_main_str_insertion_idx + 1) , pend_string);
        for (int i = 0; i < (cel_size/2) ; i++) // loop where am going to insert the whole chunk of bx in the ideal main_inserttoin indx
        {
            if (pend.empty())
                break;
            dq_it it = pend.begin() + pend_target_start_idx;
            pend.erase(it);
        }
        pend_str.erase(pend_str.begin() + pend_idx);
    }    
    this->dque = main;    
}




PmergeMe::~PmergeMe(){}
