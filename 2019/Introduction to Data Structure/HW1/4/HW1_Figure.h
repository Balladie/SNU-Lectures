#ifndef FIGURE_H
#define FIGURE_H

#include <iostream>

using namespace std;

class Figure {
protected:
	float area;

public:
	Figure();
	virtual ~Figure();

	friend ostream& operator<<(ostream&, const Figure&);

	virtual void shift(int, int) = 0;
	virtual ostream& print(ostream& os) const = 0;
};

class Rectangle : public Figure {
private:
	int width;
	int height;
	int* point;

public:
	Rectangle();
	Rectangle(int, int, int, int);
	~Rectangle();
	void shift(int, int);
	ostream& print(ostream&) const;
};

class Circle : public Figure {
private:
	int radius;
	int* center;

public:
	Circle();
	Circle(int, int, int);
	~Circle();
	void shift(int, int);
	ostream& print(ostream&) const;
};

#endif