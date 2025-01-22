#include <iostream>
#include <vector>
#include <future>
#include <stdexcept>
#include <thread>

//zadanie 1
void scalarOperation(std::promise<double>&& promiseObj, std::vector<double>& v, std::vector<double>& w) {
    try {
        if (v.size() != w.size() || v.empty() || w.empty()) {
            throw std::invalid_argument("Vector inputs are either zero size or don't have the same size");
        }

        double sum = 0.0;
        for (size_t i = 0; i < v.size(); ++i) {
            sum += v[i] * w[i];
        }

        promiseObj.set_value(sum);
    }
    catch (...) {
        promiseObj.set_exception(std::current_exception());
    }
}

//zadanie 2
namespace cpplab
{
    template<typename T>
    class allocator {
    public:
        using value_type = T;

        allocator() = default;

        T* allocate(std::size_t n) {
            return static_cast<T*>(::operator new(n * sizeof(T)));
        }

        void deallocate(T* p, std::size_t n) {
            ::operator delete(p);
        }
    };
}

int main() {
    //zadanie 2
    cpplab::allocator<int> alloc;
    std::cout << typeid(cpplab::allocator<int>::value_type).name() << std::endl;

    cpplab::allocator<int>::value_type* p_test = alloc.allocate(1);
    std::cout << *p_test << std::endl;
    *p_test = 3;
    std::cout << *p_test << std::endl;
    alloc.deallocate(p_test, 1);

    std::vector<int, cpplab::allocator<int>>v1;
    v1.push_back(13);
    v1.push_back(23);

    std::cout << *(v1.end() - 1) << std::endl;
    
    //zadanie 1
    std::vector<double> v = { 1.0, 2.0, 3.0 };
    std::vector<double> w = { 3.0, 5.0, 2.0 };
    double sum = 0.0;

    std::vector<std::promise<double>> promiseObjs(10);
    std::vector<std::future<double>> futureObjs;
    std::vector<std::thread> threads;

    for (int i = 0; i < 10; ++i) {
        futureObjs.push_back(promiseObjs[i].get_future());
        threads.emplace_back(scalarOperation, std::move(promiseObjs[i]), std::ref(v), std::ref(w));
    }

    try {
        for (int i = 0; i < 10; ++i) {
            sum += futureObjs[i].get();
        }
        std::cout << "Result: " << sum << std::endl;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    for (auto& t : threads) {
        t.join();
    }


    return 0;
}
