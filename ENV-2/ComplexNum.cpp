#include "ComplexNum.h"

ComplexNum::ComplexNum(double r, double i) : rl(r), im(i) {
}

ComplexNum ComplexNum::operator+(const ComplexNum& oth) const {
	return ComplexNum(rl + oth.rl, im + oth.im);
}
ComplexNum ComplexNum::operator-(const ComplexNum& oth) const {
	return ComplexNum(rl - oth.rl, im - oth.im);
}
ComplexNum ComplexNum::operator*(double k) const {
	return ComplexNum(rl * k, im * k);
}
double ComplexNum::abs() const {
	return std::sqrt(rl * rl + im * im);
}
std::ostream& operator<<(std::ostream& os, const ComplexNum& c) {
	os << "(" << c.rl << "," << c.im << ")";
	return os;
}
