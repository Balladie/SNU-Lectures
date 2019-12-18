#include "HW1_Array2D.h"

int main() {
	Array2D a(5);

	cout << "<Original Matrix>" << endl;
	cout << a << endl;

	Array2D b(5);
	cout << "<After MoveRight(0, 1) & MoveLeft(3, 3)>" << endl;
	b.moveRight(0, 1);
	b.moveLeft(3, 3);
	cout << b << endl;

	Array2D c(5);
	cout << "<After MoveUp(3, 2) & MoveDown(1, 6)>" << endl;
	c.moveUp(3, 2);
	c.moveDown(1, 6);
	cout << c << endl;

	Array2D d(5);
	cout << "<After MoveUpRight(3, 1) & MoveDownLeft(5, 2)>" << endl;
	d.moveUpRight(3, 1);
	d.moveDownLeft(5, 2);
	cout << d << endl;

	Array2D e(5);
	cout << "<After MoveUpLeft(3, 1) & MoveDownRight(5, 2)>" << endl;
	e.moveUpLeft(3, 1);
	e.moveDownRight(5, 2);
	cout << e << endl;

	return 0;
}