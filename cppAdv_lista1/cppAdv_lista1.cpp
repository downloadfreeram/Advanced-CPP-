#include <iostream>
#include "template_header.h"
int main()
{
    auto a = 4.6;
    auto b = 5.8;
    std::vector<int> w{23, 1, 10, 5, 2};
    my_max(a, b, ([](auto a, auto b) -> auto {return a < b ? b : a;}));
    insertion_sort(w);

    using cpplab::vector;
    vector<int> w1;
    //vector<char> w2;
    w1.add(10);
    w1.add(20);
    w1.add(30);
    w1.add(40);
    w1.print();
    w1.delete_last();
    w1.print();
    std::cout << w1.get(1);
}

