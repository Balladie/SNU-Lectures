#ifndef COMPLEX_H
#define COMPLEX_H

#include <iostream>
#include <math.h>

using namespace std;

template <class T>
class Complex {
private:
	T re;
	T im;

public:
	Complex();
	Complex(T, T);
	Complex operator+ (const Complex&);
	Complex operator- (const Complex&);
	Complex operator* (const Complex&);
	Complex operator~ () const;

	template <class U>
	friend ostream& operator<<(ostream&, const Complex<U>&);
};

template<class T>
Complex<T>::Complex()
{
	re = 0;
	im = 0;
}

template<class T>
Complex<T>::Complex(T re_part, T im_part)
{
	re = re_part;
	im = im_part;
}

template<class T>
Complex<T> Complex<T>::operator+(const Complex<T>& rhs)
{
	return Complex<T>(re + rhs.re, im + rhs.im);
}

template<class T>
Complex<T> Complex<T>::operator-(const Complex<T>& rhs)
{
	return Complex<T>(re - rhs.re, im - rhs.im);
}

template<class T>
Complex<T> Complex<T>::operator*(const Complex<T>& rhs)
{
	return Complex<T>(re * rhs.re - im * rhs.im, re * rhs.im + im * rhs.re);
}

template<class T>
Complex<T> Complex<T>::operator~() const
{
	return Complex<T>(re, 0 - im);
}

template<class U>
ostream& operator<<(ostream& os, const Complex<U>& complex)
{
	if (complex.im >= 0)
		os << "(" << complex.re << " + " << complex.im << "i)" << endl;
	else
		os << "(" << complex.re << " - " << 0.0 - complex.im << "i)" << endl;

	return os;
}

void solveQuadratic(Complex<double>& x1, Complex<double>& x2, int a, int b, int c)
{
	// We assumed that a != 0, so just returns two zeros in this case
	if (a == 0)
	{
		x1 = Complex<double>(0.0, 0.0);
		x2 = Complex<double>(0.0, 0.0);
	}
	else
	{
		int D = b * b - 4 * a * c;

		if (D >= 0)
		{
			x1 = Complex<double>((0.0 - b + sqrt(D)) / (2.0 * a), 0.0);
			x2 = Complex<double>((0.0 - b - sqrt(D)) / (2.0 * a), 0.0);
		}
		else
		{
			x1 = Complex<double>((0.0 - b) / (2.0 * a), sqrt(0.0 - D) / (2.0 * a));
			x2 = Complex<double>((0.0 - b) / (2.0 * a), 0.0 - sqrt(0.0 - D) / (2.0 * a));
		}
	}
}

#endif