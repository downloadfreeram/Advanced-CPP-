#include <iostream>
#include "template_header.h"


int main()
{
    //zad1
    auto a = 4.6;
    auto b = 5.8;
    my_max(a, b, ([](auto a, auto b) -> auto {return a < b ? b : a; }));

    //zad 2
    std::vector<int> w{ 23, 1, 10, 5, 2 };
    std::vector<std::string> w2{ "b","c","a","f","z","h"};
    insertion_sort(w);
    insertion_sort(w2);

    //zad 3
    cpplab::vector<int> w1;
    w1.push_back(1);
    w1.push_back(2);
    w1.push_back(3);
    w1.push_back(4);
    w1.push_back(5);
    w1.push_back(6);
    w1.push_back(7);
    w1.push(9, 2);
    w1.print_vector();

    w1.pop_back();
    w1.pop_back();
    w1.print_vector();

    w1.resize(2);
    w1.print_vector();
    

}

