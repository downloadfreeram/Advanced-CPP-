#include <typeinfo>
#include <vector>
// zadanie 1
template <typename T, typename C>
auto my_max(T a, T b, C comp)
{
	std::cout << typeid(a).name() << std::endl;
	std::cout << typeid(b).name() << std::endl;
	std::cout << comp(a, b) << std::endl;
}

//zadanie 2
template <typename T>
auto insertion_sort(std::vector<T> w)
{
	std::cout << "Before the insertion sort: ";
	for (int i = 0;i < w.size();i++)
	{
		std::cout << w[i] << " ";
	}
	std::cout << std::endl;
	for (int i = 1;i < w.size();i++)
	{
		int key = w[i];
		int j = i - 1;

		while (j >= 0 && w[j] > key)
		{
			w[j + 1] = w[j];
			j = j - 1;
		}
		w[j + 1] = key;
	}
	std::cout << "After the insertion sort: ";
	for (int i = 0;i < w.size();i++)
	{
		std::cout << w[i] << " ";
	}
	std::cout << std::endl;
}

namespace cpplab {
	template <typename T>
	class vector {
		T* arr;
		int vector_index;
		int vector_capacity;
	public:
		//default constructor
		vector() {
			arr = new T[1];
			vector_index = 0;
			vector_capacity = 1;
		}
		//deconstructor
		~vector() { delete[] arr; }

		void add(T value) 
		{
			if (vector_index == vector_capacity)
			{
				T* temp = new T[2 * vector_capacity];
				for (int i = 0;i < vector_capacity;i++)
				{
					temp[i] = arr[i];
				}
				delete[] arr;
				vector_capacity *= 2;
				arr = temp;
			}
			arr[vector_index] = value;
			vector_index++;
		}
		void add(T value, int index)
		{
			if (vector_index == vector_capacity) {
				add(value);
			}
			else {
				arr[index] = value;
			}
		}
		void delete_last()
		{
			vector_capacity--;
		}
		T get(int index)
		{
			if (index < vector_index) {
				return arr[index];
			}
			else {
				return -1;
			}
		}
		void print()
		{
			for (int i = 0; i < vector_capacity; i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << "\n";
		}
	};
}

