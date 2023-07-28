#include <iostream>

#include "FileSystem.hpp"

using std::cin, std::cout, std::endl;

using Data::FS::FileSystem;

void printVector(const std::vector<std::string>& v) {

	for (auto elem : v)
		cout << elem << endl;

}

int main() {

	cout << "Started" << endl;

	return 0;
}