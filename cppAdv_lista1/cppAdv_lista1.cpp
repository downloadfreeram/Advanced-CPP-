#include <iostream>
#include "template_header.h"


int main()
{
    //zad1
    auto a = 4.6;
    auto b = 5.8;
    my_max(a, b, ([](auto a, auto b) -> auto {return a < b ? b : a; }));

    //zad 2
    std::vector<int> w1{ 23, 1, 10, 5, 2 };
    std::vector<std::string> w2{ "b","c","a","f","z","h"};
    insertion_sort(w1);
    insertion_sort(w2);

    //zad 3
    cpplab::vector<double> w3;
    cpplab::vector<double> w4;
    std::vector<double> w5 = {1.5,2.5};
    w3.push_back(1.5);
    w3.push_back(2.5);

    w4.push_back(1.5);
    w4.push_back(2.5);

    auto res = w3 * w5;
    std::cout << "Dot product: " << res << std::endl;
    

}

