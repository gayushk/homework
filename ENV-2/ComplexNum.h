#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

#include <iostream>
#include <cmath>

class ComplexNum {
	public:
 	   ComplexNum(double r = 0.0, double i = 0.0);
	   ComplexNum operator+(const ComplexNum& oth) const;
	   ComplexNum operator-(const ComplexNum& oth) const;
	   ComplexNum operator*(double k) const;
	   double abs() const;

	   friend std::ostream& operator<<(std::ostream& os, const ComplexNum& c);
	private:
	   double rl, im;
};

#endif
