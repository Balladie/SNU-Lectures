#include "HW1_Figure.h"

Figure::Figure()
{
	area = 0.0f;
}

Figure::~Figure()
{

}

ostream& operator<<(ostream& os, const Figure& figure)
{
	return figure.print(os);
}

Rectangle::Rectangle()
{
	width = 0;
	height = 0;
	point = nullptr;
	area = 0;
}

Rectangle::Rectangle(int x1, int y1, int x2, int y2)
{
	if (x1 < x2 && y1 < y2)
	{
		width = x2 - x1;
		height = y2 - y1;
		area = (float)width * height;

		point = new int[4];
		point[0] = x1;
		point[1] = y1;
		point[2] = x2;
		point[3] = y2;
	}
	else
	{
		width = 0;
		height = 0;
		point = nullptr;
		area = 0;
	}
}

Rectangle::~Rectangle()
{
	width = 0;
	height = 0;
	area = 0;

	if (point != nullptr)
		delete[] point;
}

void Rectangle::shift(int _x, int _y)
{
	if (point != nullptr)
	{
		point[0] += _x;
		point[1] += _y;
		point[2] += _x;
		point[3] += _y;
	}
}

ostream& Rectangle::print(ostream& os) const
{
	os << "Figure: rectangle" << '\n';

	if (point != nullptr)
	{
		os << "Width: " << width << ", Height: " << height << " -> Area: " << area << '\n';
		os << "The coordinate of diagonal line: (" << point[0] << ", " << point[1] << "), (" << point[2] << ", " << point[3] << ")" << '\n';
	}

	return os;
}

Circle::Circle()
{
	radius = 0;
	center = nullptr;
	area = 0;
}

Circle::Circle(int cx, int cy, int r)
{
	center = new int[2];
	center[0] = cx;
	center[1] = cy;

	radius = r;
	area = 3.14f * r * r;
}

Circle::~Circle()
{
	radius = 0;
	area = 0;

	if (center != nullptr)
		delete[] center;
}

void Circle::shift(int _x, int _y)
{
	if (center != nullptr)
	{
		center[0] += _x;
		center[1] += _y;
	}
}

ostream& Circle::print(ostream& os) const
{
	os << "Figure: circle" << '\n';

	if (center != nullptr)
	{
		os << "Radius: " << radius << " -> Area: " << area << '\n';
		os << "The coordinate of center: (" << center[0] << ", " << center[1] << ")" << '\n';
	}

	return os;
}