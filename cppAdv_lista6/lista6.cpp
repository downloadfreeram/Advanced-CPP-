#include <iostream>
#include <vector>
#include <random>
#include <thread>
#include <algorithm>
#include <functional>
//zadanie 1
void sort_half(std::vector<int> w)
{
    std::cout << "Thread 1 started" << std::endl;
    std::sort(w.begin(), w.begin() + w.size() / 2);
    for (auto i : w)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Thread 1 done" << std::endl;
}
void sort_rest(std::vector<int> w)
{
    std::cout << "Thread 2 started" << std::endl;
    std::sort(w.begin() + w.size() / 2, w.end());
    for (auto i : w)
    {
        std::cout << i << std::endl;
    }
    std::cout << "Thread 2 done" << std::endl;
}
//zadanie 2
class thread_pool {
public:

    void add_task(std::function<double()> task) {

    }
    double average() {

    }
    void stop() {

    }

    ~thread_pool() = default;
private:
    std::function<double()> tasks;
};
int main()
{
    srand(time(NULL));
    std::vector<int> v;
    for (int i = 0;i < 1000;i++)
    {
        v.push_back(rand() % 100 + 1);
    }
    std::thread t1(sort_half, std::ref(v));
    t1.join();
    std::thread t2(sort_rest, std::ref(v));
    t2.join();
    return 0;
}
