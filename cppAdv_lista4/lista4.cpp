#include <iostream>
#include <vector>

namespace cpplab {
	template <typename T>
	class vector {
	private:
		T* arr;
		size_t vector_size = 0;
		T value_type;
	public:
		// default constructor
		vector() {
			arr = new T[0];
			vector_size = 0;
		}
		// copy constructor
		vector(const vector& other) : arr(new T[other.size()]), vector_size(other.size())
		{
			std::copy(other.arr, other.arr + other.size(), arr);
			std::cout << "Copied" << std::endl;
		}
		//copy assignement operator
		vector& operator=(const vector& other)
		{
			if (this != &other)
			{
				delete[] arr;
				arr = new int[other.size()];
				vector_size = other.size();
				std::copy(other.arr, other.arr + other.size(), arr);
			}
			std::cout << "Used copy assignement" << std::endl;
			return *this;
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

		// deconostructor
		~vector() { delete[] arr; std::cout << "Destroyed" << std::endl; }
	};
}

template <typename U, typename W>
auto operator*(const U& vec1, const W& vec2)
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

int main() {

	cpplab::vector<int> a;
	cpplab::vector<int> b = a;
	cpplab::vector<int> c;
	c = a;

	a.push_back(3);

	a.print_vector();
	

}