#include <iostream>
#include <vector>
#include <memory>
#include <utility>
#include <random>
#include <concepts>
#include <type_traits>

//zadanie 1
template<typename T>
class BST
{
public:
	struct Node
	{
		std::shared_ptr<Node> left = nullptr;
		std::shared_ptr<Node> right = nullptr;
		std::weak_ptr<Node> parent;
		T key;
	};

	std::shared_ptr<Node> insert(std::shared_ptr<Node>& root, T value)
	{
		if (root == nullptr)
		{
			root = std::make_shared<Node>();
			root->key = value;
			return root;
		}
		if (value < root->key)
		{
			auto tmp = insert(root->left, value);
			if (tmp < root->left)
			{
				root->left->parent = root;
			}
			return root->left;
		}
		else
		{
			auto tmp = insert(root->right, value);
			if (tmp < root->right)
			{
				root->right->parent = root;
			}
			return root->right;
		}
	}
	void print_in_order(std::shared_ptr<Node> root)
	{
		if (root == nullptr)
		{
			return;
		}
		print_in_order(root->left);
		std::cout << root->key << " ";
		print_in_order(root->right);
	}
};

//zadanie 2
namespace cpplab
{
	template<typename T>
	class unique_ptr
	{
	public:
		unique_ptr() = default;
		explicit unique_ptr(T* data) : data(data) {}

		~unique_ptr() { reset(); }

		unique_ptr(unique_ptr&& other) noexcept : data(std::exchange(other.data, nullptr)) {}
		unique_ptr& operator=(unique_ptr&& other) noexcept
		{
			if (this != &other)
			{
				reset();
				data = std::exchange(other.data, nullptr);
			}
			return *this;
		}

		unique_ptr(const unique_ptr&) = delete;
		unique_ptr& operator=(const unique_ptr&) = delete;

		void reset(T* new_data = nullptr)
		{
			delete data;
			data = new_data;
		}

		T* release()
		{
			return std::exchange(data, nullptr);
		}

		T* get() const { return data; }
		T& operator*() const { return *data; }
		T* operator->() const { return data; }

		bool operator!() const { return data == nullptr; }

	private:
		T* data = nullptr;
	};
}


template<typename T>
concept notNull = std::is_pointer_v<T> && !std::is_same_v<T, std::nullptr_t>;

template<notNull T>
class non0_ptr {
private:
	T data;

public:
	explicit non0_ptr(T data) : data(data) {
		if (data == nullptr) {
			throw std::invalid_argument("ERROR: pointer cannot be initialized with nullptr");
		}
	}

	T get() const { return data; }

	decltype(auto) operator*() const { return *data; }

	explicit operator bool() const { return true; }

	~non0_ptr() = default;
};

//zadanie 3
class Task {
private:
	int N, maxWeight;
	std::vector<std::vector<int>> items; // items[i][0] = weight, items[i][1] = value
	std::vector<std::vector<int>> memory;

	int taskRecursive(int maxWeight, int n) {
		if (n == 0 || maxWeight == 0) {
			return 0;
		}

		// if the result is computed return it
		if (memory[n][maxWeight] != -1) {
			return memory[n][maxWeight];
		}

		// if the weight of a current element is larger than the capacity of the storage, skip it
		if (items[n - 1][0] > maxWeight) {
			memory[n][maxWeight] = taskRecursive(maxWeight, n - 1);
		}
		else {
			// choose the maximum out of skipping the value or keeping it
			memory[n][maxWeight] = std::max(
				taskRecursive(maxWeight, n - 1),
				items[n - 1][1] + taskRecursive(maxWeight - items[n - 1][0], n - 1)
			);
		}

		return memory[n][maxWeight];
	}

public:
	Task(int n, int w, const std::vector<std::vector<int>>& itemsVec) : N(n), maxWeight(w), items(itemsVec) {
		memory.resize(N + 1, std::vector<int>(maxWeight + 1, -1));
	}

	int solve() {
		return taskRecursive(maxWeight, N);
	}
};

int main()
{
	BST<int> tree;
	std::shared_ptr<BST<int>::Node> root = nullptr;

	tree.insert(root, 40);
	tree.insert(root, 10);
	tree.insert(root, 5);
	tree.insert(root, 30);
	tree.insert(root, 50);
	tree.insert(root, 78);
	tree.insert(root, 20);
	tree.insert(root, 60);
	tree.insert(root, 67);

	tree.print_in_order(root);
	
	cpplab::unique_ptr<int> ptr1(new int(10));
	cpplab::unique_ptr<int> ptr2(new int(20));

	std::cout << *ptr1 << std::endl;
	ptr1.reset(new int(30));
	std::cout << *ptr1 << std::endl;

	int* raw_ptr = ptr2.release();
	std::cout << (ptr2.get() == nullptr ? "nullptr" : "not nullptr") << std::endl;
	delete raw_ptr;

	try {
		non0_ptr<int*> ptr(new int(5));
		std::cout << "Value: " << *ptr << std::endl;

		// this line will throw an error
		// non0_ptr<int*> nullPtr(nullptr);
	}
	catch (const std::exception& e) {
		std::cerr << e.what() << std::endl;
	}

	srand(time(NULL));

	// dummy data
	int N = 10;
	int maxWeight = 100;

	std::vector<std::vector<int>> items;

	for (int i = 0; i < N; i++) {
		int weight = rand() % maxWeight + 1;
		int value = rand() % 100 + 1;
		items.push_back({ weight, value });
	}

	std::cout << "\nContent of the vault:\n";
	for (const auto& item : items) {
		std::cout << "Weight: " << item[0] << ", Value: " << item[1] << std::endl;
	}

	Task task(N, maxWeight, items);
	int maxProfit = task.solve();
	std::cout << "Max value that is possible: " << maxProfit << std::endl;

	return 0;
}