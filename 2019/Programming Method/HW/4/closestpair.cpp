#include <iostream>
#include <time.h>
#include <cmath>

#define MAX_DIST_FOR_1_DIM (double)(10 * 300)

using namespace std;

class point
{
private:
    int x, y;
public:
    point() {};
    ~point() {};
    void set(int a, int b)
    {
        x = a;
        y = b;
    }
    int getx() { return x; };
    int gety() { return y; };
};

inline double dist(point a, point b)
{
    return sqrt(pow(a.getx() - b.getx(), 2) + pow(a.gety() - b.gety(), 2));
}

// A Naive closest algorithm
double closest_naive(point* input, int size)
{
    double min;

	// Set initial min as a distance of point[0]~point[1]
	min = dist(input[0], input[1]);

	// Find min when the index of the first point operand is 0,
    // because we already set distance of point[0]~point[1] as initial value of min.
    for (int j = 2; j < size; j++)
    {
		double tmpDist = dist(input[0], input[j]);

        if (tmpDist < min)
        {
            min = tmpDist;
        }
    }

	// Find min when the index of the first point operand is not 0
    for (int i = 1; i < size; i++)
    {
        for (int j = i + 1; j < size; j++)
        {
			double tmpDist = dist(input[i], input[j]);

            if (tmpDist < min)
            {
                min = tmpDist;
            }
        }
    }

	return min;
}

// Swaps the value of x and y in two different points
void swap(point &p1, point &p2)
{
    int tmpX = p1.getx();
    int tmpY = p1.gety();

	p1.set(p2.getx(), p2.gety());
    p2.set(tmpX, tmpY);
}

void insertion_sort_by_x(point* input, int n)
{
	for (int i = 1; i < n; ++i)
	{
		int keyX = input[i].getx();
		int keyY = input[i].gety();
		int j;

		for (j = i - 1; j >= 0; --j)
		{
			int cur = input[j].getx();

			if (cur <= keyX)
			{
				input[j + 1].set(keyX, keyY);
				break;
			}
			else
			{
				input[j + 1].set(cur, input[j].gety());
			}
		}
		
		if (j == -1)
		{
			input[0].set(keyX, keyY);
		}
	}
}

int partition_points_by_x(point* input, int l, int r, int x)
{
	int k, i, j;

	for (k = l; k < r; ++k)
	{
		if (input[k].getx() == x)
		{
			break;
		}
	}

	swap(input[k], input[r]);

	i = l;
	for (j = i; j <= r - 1; ++j)
	{
		if (input[j].getx() <= input[r].getx())
		{
			swap(input[i], input[j]);
			++i;
		}
	}

	swap(input[i], input[r]);
	return i;
}

int partition_points_by_y(point* input, int l, int r, int k)
{
	point* pivot = &input[k];

	int i = l - 1;
	int j = r + 1;

	while(1)
	{
		do
		{
			++i;
		} while (input[i].gety() < pivot->gety());

		do
		{
			--j;
		} while (input[j].gety() > pivot->gety());

		if (i >= j)
		{
			return j;
		}

		swap(input[i], input[j]);
	}
}

int quick_select_points_by_x(point* input, int l, int r, int k)
{
	int medOfMed;
	int size = r - l + 1;
	int numOfMed;
	int posOfPartitioned;
	int i;

	if (l == r)
	{
		return input[l].getx();
	}

	for (i = 0; i < size / 5; ++i)
	{
		insertion_sort_by_x(input + l + 5 * i, 5);
	}
	if (5 * i < size)
	{
		insertion_sort_by_x(input + l + 5 * i, size - 5 * i);
	}

	numOfMed = (size + 4) / 5;
	point* medArray = new point[numOfMed];
	
	for (i = 0; i < numOfMed - 1; ++i)
	{
		medArray[i].set(input[l +  5 * i + 2].getx(), input[l + 5 * i + 2].gety());
	}

	if (size % 5 == 0)
	{
		medArray[i].set(input[l +  5 * i + 2].getx(), input[l + 5 * i + 2].gety());
	}
	else
	{
		medArray[i].set(input[l + 5 * i + (size % 5 - 1) / 2].getx(), input[l + 5 * i + (size % 5 - 1) / 2].gety());
	}

	medOfMed = quick_select_points_by_x(medArray, 0, numOfMed - 1, (numOfMed - 1) / 2);
	posOfPartitioned = partition_points_by_x(input, l, r, medOfMed);

	delete[] medArray;

	if (posOfPartitioned == k)
	{
		return input[posOfPartitioned].getx();
	}
	else if (posOfPartitioned < k)
	{
		return quick_select_points_by_x(input, posOfPartitioned + 1, r, k);
	}
	return quick_select_points_by_x(input, l, posOfPartitioned - 1, k);
}

void quick_sort_points_by_y(point* input, int l, int r)
{
	if (l < r)
	{
		int pIndex = partition_points_by_y(input, l, r, (r - l) / 2 + l);
		quick_sort_points_by_y(input, l, pIndex);
		quick_sort_points_by_y(input, pIndex + 1, r);
	}
}

double abs(double &a)
{
	if (a >= 0)
	{
		return a;
	}
	return -a;
}

double stripClosest(point* strip, int n, double d)
{
	double min = d;

	for (int i = 0; i < n; ++i)
	{
		for (int j = i + 1; j < n && (strip[j].gety() - strip[i].gety()) < min; ++j)
		{
			double tmpDist = dist(strip[i], strip[j]);

			if (tmpDist < min)
			{
				min = tmpDist;
			}
		}
	}

	delete[] strip;

	return min;
}

double min_double(double a, double b)
{
	if (a > b)
	{
		return b;
	}
	return a;
}

int getIndexOfPByX(point* input, int l, int r, int p)
{
	int k;
	int cntOfSame = 0;

	for (k = l; k <= r; ++k)
	{
		if (input[k].getx() == p)
		{
			break;
		}
	}
	for (; k <= r; ++k)
	{
		if (input[k].getx() != p)
		{
			break;
		}
		++cntOfSame;
	}

	return k - (cntOfSame / 2 + 1);
}

double getClosestNaiveBase(point* input, int l, int r)
{
	double min = MAX_DIST_FOR_1_DIM;

	for (int i = l; i <= r - 1; ++i)
	{
		for (int j = i + 1; j <= r; ++j)
		{
			double tmpDist = dist(input[i], input[j]);
			if (tmpDist < min)
			{
				min = tmpDist;
			}
		}
	}

	return min;
}

double getClosest(point* input, int l, int r, point* inputSortedByY)
{
	const int size = r - l + 1;
	point* strip = new point[size];
	point* inputSortedByYLeft;
	point* inputSortedByYRight;
    double min;
	double minOfLeft, minOfRight;
	double rangeOfMerge;
	int medianOfX;
	int indexOfMedianOfX;
	int j = 0;
	int cntYLeft = 0, cntYRight = 0;

	if (l == r)
	{
		return MAX_DIST_FOR_1_DIM;
	}
	if (r - l <= 2)
	{
		return getClosestNaiveBase(input, l, r);
	}

	medianOfX = quick_select_points_by_x(input, l, r, (l + r) / 2);

	indexOfMedianOfX = getIndexOfPByX(input, l, r, medianOfX);

	inputSortedByYLeft = new point[indexOfMedianOfX - l + 1];
	inputSortedByYRight = new point[r - indexOfMedianOfX];

	for (int i = 0; i < size; ++i)
	{
		if (inputSortedByY[i].getx() <= medianOfX)
		{
			inputSortedByYLeft[cntYLeft++].set(inputSortedByY[i].getx(), inputSortedByY[i].gety());
		}
		else
		{
			inputSortedByYRight[cntYRight++].set(inputSortedByY[i].getx(), inputSortedByY[i].gety());
		}
	}

	minOfLeft = getClosest(input, l, indexOfMedianOfX, inputSortedByYLeft);
	minOfRight = getClosest(input, indexOfMedianOfX + 1, r, inputSortedByYRight);

	rangeOfMerge = (minOfLeft <= minOfRight) ? minOfLeft : minOfRight;

	for (int i = 0; i < size; ++i)
	{
		if (abs(inputSortedByY[i].getx() - medianOfX) < rangeOfMerge)
		{
			strip[j].set(inputSortedByY[i].getx(), inputSortedByY[i].gety());
			++j;
		}
	}

	delete[] inputSortedByYLeft;
	delete[] inputSortedByYRight;
	delete[] inputSortedByY;

	cout << "Test" << endl;
	return min_double(stripClosest(strip, j, rangeOfMerge), rangeOfMerge);
}

double closest(point* input, int l, int r)
{
	const int size = r - l + 1;
	point* inputSortedByY = new point[size];

	for (int i = 0; i < size; ++i)
	{
		inputSortedByY[i].set(input[i].getx(), input[i].gety());
	}

	quick_sort_points_by_y(inputSortedByY, l, r);

	return getClosest(input, l, r, inputSortedByY);
}

int main()
{
    int size = 300;
    point* arr = new point[size];

	int tempx, tempy;
    srand((unsigned int)time(NULL));

	for (int i = 0; i < size; i++)
    {
        tempx = rand() % (10 * size) - 5 * size;
        tempy = rand() % (10 * size) - 5 * size;
        arr[i].set(tempx, tempy);
    }

	clock_t begin, end;
    double min1, min2;    begin = clock();
    min1 = closest_naive(arr, size);
    end = clock();
    cout << "Naive algorithm\n" << "Min distance : " << min1 << endl;
    cout << "Elapsed time : " << (end - begin) << endl;    begin = clock();
    min2 = closest(arr, 0, size - 1);
    end = clock();
    cout << "Divide and conquer algorithm\n" << "Min distance : " << min2 << endl;
    cout << "Elapsed time : " << (end - begin) << endl;

	return 0;
}
