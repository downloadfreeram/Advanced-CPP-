#include <iostream>
#include <vector>
#include <utility>

//zadanie 1
template <typename T>
auto insertion_sort(std::vector<T> w)
{
	std::cout << "Before the insertion sort: ";
	for (int i = 0; i < w.size(); i++)
	{
		std::cout << w[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 1; i < w.size(); i++)
	{
		T key = w[i];
		int j = i - 1;

		while (j >= 0 && w[j] > key)
		{
			w[j + 1] = w[j];
			j = j - 1;
		}
		w[j + 1] = key;
	}
	std::cout << "After the insertion sort: ";
	for (int i = 0; i < w.size(); i++)
	{
		std::cout << w[i] << " ";
	}
	std::cout << std::endl;
}
template <>
auto insertion_sort(std::vector<std::string> w)
{
	std::cout << "ema eniu" << std::endl;
}

//zadanie 2
template <int N>
struct Factorial
{
	enum { value = N * Factorial<N - 1>::value };
};

template <>
struct Factorial<0>
{
	enum { value = 1 };
};

//zadanie 3
template <typename T>
void print_all(T param)
{
	std::cout << param << std::endl;
}
template <typename T, typename...Ts>
constexpr void print_all(T&& first, Ts&&... rest) 
{
	if constexpr (sizeof...(Ts) == 0)
	{
		std::cout << first;
	}
	else
	{
		std::cout << first << " ";
		print_all(std::forward<Ts>(rest)...);
	}
}

int main()
{
	std::vector<int> w = { 2,5,1,11,3 };
	std::vector<std::string> w2 = { "aa","ab","ac" };
	insertion_sort(w);
	insertion_sort(w2);
	std::cout << Factorial<5>::value << std::endl;
	print_all("string", 1.002, 20.8, 'c', 4.04f);
};