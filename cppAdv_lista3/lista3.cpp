#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <type_traits>
#include <concepts>


//zadanie 1
template <typename T, typename U>
concept isSame = std::same_as<T, U>;

template <typename T, typename U>
concept sameSize = requires(T w1, U w2) {
    { w1.size() == w2.size() } -> std::convertible_to<bool>;
};

template <typename T, typename U>
concept isArithmetic = std::is_arithmetic_v<typename T::value_type> &&
std::is_arithmetic_v<typename U::value_type>;

template <typename U, typename W>
requires isSame<U, W>&& isArithmetic<U, W> && sameSize<U, W>
auto operator*(U& vec1, W& vec2)
{
    if(vec1.size() != vec2.size())
    {
        throw std::invalid_argument("Vectors must be the same size");
    }
	using ValueType = decltype(vec1[0] * vec2[0]);
	ValueType dotProduct = 0;

	for (size_t i = 0; i < vec1.size(); i++)
	{
		dotProduct += vec1[i] * vec2[i];
	}
	return dotProduct;
}
//zadanie 2
template<typename T>
auto as_sorted_view(std::vector<T>& w) {
	std::vector<T*> v;
	for (int i = 0; i < w.size(); i++)
	{
		v.push_back(&w[i]);
	}
	std::sort(v.begin(), v.end(), [](T* a, T* b) {return (*a < *b); });
	return v;
}


//zadanie 3
template<typename T>
struct Node {
	T data;
	std::unique_ptr<Node> next;
	Node(T data) : data(data), next(nullptr) {};
};
template <typename T>
class forwardList {
public:
	std::unique_ptr<Node<T>> head;
	forwardList() :head(nullptr) {};
	
	void insert(T value)
	{
		auto new_node = std::make_unique<Node<T>>(value);
		new_node->next = std::move(head);
		head = std::move(new_node);
	}

	void printList()
	{
		auto current = head.get();

		while (current)
		{
			std::cout << current->data << ", ";
			current = current->next.get();
		}
		std::cout << std::endl;
	}

	void reverse()
	{
		std::unique_ptr<Node<T>> previous = nullptr;
		std::unique_ptr<Node<T>> current = std::move(head);
		std::unique_ptr<Node<T>> next = nullptr;

		while (current != nullptr)
		{
			next = std::move(current->next);
			current->next = std::move(previous);
			previous = std::move(current);
			current = std::move(next);
		}

		head = std::move(previous);
	}
	
};

int main() {
	//zadanie 1
	std::vector<int> w1 = { 2,4,5 };
	std::vector<int> w2 = { 3,6,7 };
	std::vector<float> w3 = { 2.8,3.6,1.3 };

	std::vector<std::string> w4 = { "siema","eniu","z afrika" };
	std::vector<std::string> w5 = { "siema","eniu","z afrika" };

    	std::vector<int> w6 = { 4,5,6,8,9 };

	//dot product with same type
	auto dot_res2 = w1 * w2;
	std::cout << "Dot product: " << dot_res2 << std::endl;

	//throws an error, because these are strings which are not arithmetical
	//std::cout << w4*w5 << std::endl;

	//throws an error, because these aren't the same type
	//std::cout << w2*w3 << std::endl;

    	//throws an error because, vector sizes doesn't match
    	//std::cout << w2*w6 << std::endl;
	
    //zadanie 2
	std::vector<std::string> v_test = { "zupa","kura","jajo","arbuz","babilon" };

	auto v_output = as_sorted_view(v_test);
	
	for (auto& w : v_output)
		std::cout << *w << std::endl;

	std::cout << std::endl;

	for (auto& v : v_test)
		std::cout << v << std::endl;

	//zadanie 3
	forwardList<int> list1;

	list1.insert(1);
	list1.insert(2);
	list1.insert(4);
	list1.insert(5);
	list1.insert(9);

	list1.printList();

	list1.reverse();
	list1.printList();
	
}
