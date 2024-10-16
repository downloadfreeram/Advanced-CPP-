#include <iostream>
#include "template_header.h"


int main()
{
    //zadanie 1
    auto a = 4.6;
    auto b = 5.8;
    my_max(a, b, ([](auto a, auto b) -> auto {return a < b ? b : a; }));

    //zadanie 2
    std::vector<int> w1{ 23, 1, 10, 5, 2 };
    std::vector<std::string> w2{ "b","c","a","f","z","h"};
    insertion_sort(w1);
    insertion_sort(w2);

    //zadanie 3
    cpplab::vector<double> w3;
    cpplab::vector<double> w4;
    std::vector<double> w5 = {1.5,2.5};
    w3.push_back(1.5);
    w3.push_back(2.5);

    w4.push_back(3.5);
    w4.push_back(5.5);

    //dot product with different vectors
    auto dot_res = w3 * w5;
    std::cout << "Dot product: " << dot_res << std::endl;

    //dot product with same vectors
    auto dot_res2 = w3 * w4;
    std::cout << "Dot product: " << dot_res2 << std::endl;

    
    

}

