#include <iostream>
#include <vector>
#include "ComplexNum.h"
#include "sort.h"

int main() {
	std::vector<ComplexNum> nums = {
		ComplexNum(3,4), ComplexNum(1,2), 
		ComplexNum(0,5), ComplexNum(5,0),
		ComplexNum(5,12)
	};
	sortCompNum(nums);
	for(auto& c : nums) {
		std::cout << c << " | abs = " << c.abs() << "\n";
	}
	return 0;
}
