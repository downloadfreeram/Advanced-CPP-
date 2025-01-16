#include <iostream>
#include <vector>
#include <future>

double scalarOperation(std::vector<double>& v, std::vector<double>& w) {
	if (v.size() != w.size() || v.size() == 0 || w.size() == 0) {
		return -1;
	}
	else {
		double sum = 0.0;
		for (int i = 0;i <= v.size();i++)
		{
			sum += v[i] * w[i];
		}
		return sum;
	}
}
int main() {
	std::vector<double> v = { 1.0,2.0,3.0 };
	std::vector<double> w = { 3.0,5.0,2.0 };
	std::cout << scalarOperation(v, w) << "\n";
	return 0;
}