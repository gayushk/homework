#include <iostream>

int main(int argc, char** argv) {
	if(argc <= 1) {
		return 0;
	}
	for(int i = argc - 1; i >= 1; --i) {
		std::cout << argv[i] << " ";
       	}
	return 0;
}
