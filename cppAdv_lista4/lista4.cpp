#include <iostream>
#include <vector>

namespace cpplab {
	template <typename T>
	class vector {
	private:
		T* arr;
		size_t vector_size;
		size_t vector_capacity;
		T value_type;
	public:
		// default constructor
		vector() {
			arr = new T[0];
			vector_size = 0;
			vector_capacity = 0;
		}
		vector(std::initializer_list<T> list)
		{
			for (T& val : list)
			{
				push_back(val);
			}
		}
		// copy constructor
		vector(const vector& other) : arr(new T[other.size()]), vector_size(other.size()), vector_capacity(other.size() + 2)
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
				vector_capacity = other.size() + 2;
				std::copy(other.arr, other.arr + other.size(), arr);
			}
			std::cout << "Used copy assignement operator" << std::endl;
			return *this;
		}
		//move constructor
		vector(vector&& other) : arr(other.arr),vector_size(other.vector_size),vector_capacity(other.vector_capacity)
		{
			other.arr = nullptr;
			other.vector_size = 0;
			other.vector_capacity = 0;
			std::cout << "Moved!" << std::endl;
		}
		//move assignement operator
		vector& operator=(vector&& other)
		{
			if (this != &other)
			{
				delete[] arr;
				arr = other.arr;
				vector_size = other.vector_size;
				vector_capacity = other.vector_capacity;
				other.arr = nullptr;
				other.vector_size = 0;
				other.vector_capacity = 0;
			}
			std::cout << "Used move assignement operator" << std::endl;
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
			if (vector_size == vector_capacity)
			{
				T* temp = new T[vector_capacity + 2];

				for (size_t i = 0;i < vector_size;i++)
				{
					temp[i] = arr[i];
				}
				delete[] arr;
				vector_capacity += 2;
				arr = temp;
			}
			arr[vector_size] = value;
			vector_size++;
		}
		void resize(int new_capacity)
		{
			if (new_capacity < vector_size)
			{
				throw std::invalid_argument("ERROR: New value is greater than the vector size");
			}
			else
			{
				T* temp = new T[new_capacity];
				for (size_t i = 0;i < vector_size;i++)
				{
					temp[i] = arr[i];
				}
				vector_capacity = new_capacity;
				delete[] arr;
				arr = temp;
			}
		}
		template<typename... args>
		void emplace_back(args&&... values)
		{
			if (vector_size == vector_capacity)
			{
				resize(vector_capacity + 2);
			}
			arr[vector_size++] = T(std::forward<args>(values)...);
		}
		size_t size() const { return vector_size; }
		void print_vector()
		{	
			for (size_t i = 0; i < vector_size; i++)
			{
				std::cout << arr[i] << " ";
			}
			std::cout << std::endl;
		}
		// deconstructor
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

class pixel {
public:
	pixel() = default;
	pixel(int red, int green, int blue) : r(red), g(green), b(blue) {}

	friend std::ostream& operator<<(std::ostream& os, const pixel& p)
	{
		return os << "[" << p.r << "," << p.g << "," << p.b << "]";
	}
private:
	int r, g, b;
};

int main() {
	//zadanie 1
	cpplab::vector<int> a;
	cpplab::vector<int> b = a;
	cpplab::vector<int> c;
	c = a;
	cpplab::vector<int> d = std::move(a);
	cpplab::vector<int> e;
	e = std::move(b);

	a.push_back(3);
	a.push_back(4);

	a.print_vector();

	//zadanie 2
	cpplab::vector <pixel> p1;
	p1.emplace_back(1, 2, 3);
	p1.emplace_back(4, 5, 6);
	p1.print_vector();
}
