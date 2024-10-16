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

//zadanie 3
namespace cpplab {
	template <typename T>
	class vector {
	private:
		T* arr;
		size_t vector_size = 0;
		T value_type;
	public:
		vector() {
			arr = new T[0];
			vector_size = 0;
		}
		T& operator[] (size_t index)
		{
			if (index >= vector_size)
				throw std::out_of_range("ERROR: Index out of range");

			return arr[index];
		}
		void push_back(const T& value)
		{
			T* temp = new T[vector_size + 1];
			for (size_t i = 0; i < vector_size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			temp[vector_size] = value;
			arr = temp;
			vector_size++;
			
		}
		void push(const T& value, size_t index)
		{
			if (index >= vector_size)
				throw std::out_of_range("ERROR: Index out of range");
			T* temp = new T[vector_size];
			for (size_t i = 0; i < vector_size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			temp[index] = value;
			arr = temp;
		}
		void pop_back()
		{
			T* temp = new T[vector_size - 1];
			for (size_t i = 0; i < vector_size - 1; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = temp;
			vector_size--;
		}
		void resize(const int new_size)
		{
			if (new_size >= vector_size)
				throw std::invalid_argument("ERROR: The resize value is greater than the vector length ");
			T* temp = new T[new_size];
			for (size_t i = 0; i < new_size; i++)
			{
				temp[i] = arr[i];
			}
			delete[] arr;
			arr = temp;
			vector_size = new_size;
		}
		size_t size() const { return vector_size; }
		void print_vector()
		{
			for (size_t i = 0; i < vector_size; i++)
			{
				std::cout << arr[i] << std::endl;
			}
			std::cout << std::endl;
		}


		~vector() { delete[] arr; }
	};
}

template <typename U, typename W>
auto operator*(U &vec1, W &vec2)  
{
	if (vec1.size() != vec2.size())
		throw std::invalid_argument("ERROR: Vectors length do not match");

	using ValueType = decltype(vec1[0] * vec2[0]);
	ValueType dotProduct = 0;

	for (size_t i = 0; i < vec1.size(); i++)
	{
		dotProduct += vec1[i] * vec2[i];
	}
	return dotProduct;
}