#pragma once

#include <iostream>

class Complex {
private:
	double re = 0.0;
	double im = 0.0;
public:
	Complex(double a = 0.0, double b = 0.0) {
		re = a;
		im = b;
	}
	Complex(const Complex& z) {
		re = z.re;
		im = z.im;
	}
	~Complex() {}
	double GetRe() const {
		return re;
	}
	double GetIm() const {
		return im;
	}
	Complex& operator=(Complex z) {
		std::swap(re, z.re);
		std::swap(im, z.im);
		return *this;
	}
	Complex& operator+=(const Complex& z) {
		re += z.re;
		im += z.im;
		return *this;
	}
	Complex& operator-=(const Complex& z) {
		re -= z.re;
		im -= z.im;
		return *this;
	}
	Complex& operator*=(const Complex& z) {
		re = re * z.re - im * z.im;
		im = re * z.im + im * z.re;
		return *this;
	}
	Complex& operator/=(const Complex& z) {
		if (z.re == 0 && z.im == 0) {
			throw std::exception("Devided by zero");
		} else {
			re = (re * z.re - im * z.im) / (z.re * z.re + z.im * z.im);
			im = (re * z.im + im * z.re) / (z.re * z.re + z.im * z.im);
			return *this;
		}
	}
	Complex& operator++() {
		*this += 1;
		return *this;
	}
	Complex& operator--() {
		*this -= 1;
		return *this;
	}
	Complex operator++(int) {
		Complex copy = *this;
		++(*this);
		return copy;
	}
	Complex operator--(int) {
		Complex copy = *this;
		--(*this);
		return copy;
	}
	void Print() {
		std::cout << re << ((im >= 0) ? " + " : " ") << im << "*i\n";
	}
};

Complex operator+(const Complex& a, const Complex& b) {
	Complex copy = a;
	copy += b;
	return copy;
}
Complex operator-(const Complex& a, const Complex& b) {
	Complex copy = a;
	copy -= b;
	return copy;
}
Complex operator*(const Complex& a, const Complex& b) {
	Complex copy = a;
	copy *= b;
	return copy;
}
Complex operator/(const Complex& a, const Complex& b) {
	Complex copy = a;
	copy /= b;
	return copy;
}
bool operator<(const Complex& a, const Complex& b) {
	return a.GetRe() * a.GetRe() + a.GetIm() * a.GetIm() < b.GetRe() * b.GetRe() + b.GetIm() * b.GetIm();
}
bool operator>(const Complex& a, const Complex& b) {
	return b < a;
}
bool operator==(const Complex& a, const Complex& b) {
	return !(a < b || b < a);
}
bool operator!=(const Complex& a, const Complex& b) {
	return !(a == b);
}
std::ostream& operator<<(std::ostream& out, const Complex& z) {
	out << z.GetRe() << ((z.GetIm() >= 0) ? " + " : " ") << z.GetIm() << "*i";
	return out;
}