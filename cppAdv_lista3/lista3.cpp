#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>


//zadanie 2
template<typename T>
auto as_sorted_view(std::vector<T> w) {
	std::sort(w.begin(), w.end());
	return w;
}


//zadanie 3
template<typename T>
class Node {
public:
	int data;
	std::unique_ptr<Node> step;
	Node(T data) : data{ data }, step{ nullptr } {}
	~Node() { std::cout << "Destroyed: " << data << std::endl; }
};


int main() {

	std::vector<std::string> v_test = { "zupa","kura","jajo","arbuz","babilon" };

	auto v_output = as_sorted_view(v_test);
	
	for (auto& w : v_output)
		std::cout << w << std::endl;

	std::cout << std::endl;

	for (auto& v : v_test)
		std::cout << v << std::endl;

	auto n0{ std::make_unique<Node<int>>(0) };

	auto n1{ std::make_unique<Node<int>>(1) };
	n1->step = std::move(n0);

	auto n2{ std::make_unique<Node<int>>(2) };
	n2->step = std::move(n1);

}