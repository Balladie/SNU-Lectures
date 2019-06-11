#include <iostream>

using namespace std;

int rodCut(int *p, int n)
{
	int *r = new int[n + 1];

	r[0] = 0;
	r[1] = p[0];
	cout << "r[0] = " << r[0] << endl;
	cout << "r[1] = " << r[1] << endl;

	for (int i = 2; i <= n; i++)
	{
		r[i] = 0;
		for (int j = 1; j <= i; j++)
		{
			int tmp = p[j - 1] + r[i - j];

			if (r[i] < tmp)
				r[i] = tmp;
		}
		cout << "r[" << i << "] = " << r[i] << endl;
	}

	return r[n];
}

int main()
{
	int n;
	int *p;

	cin >> n;
	p = new int[n];
	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}

	cout << rodCut(p, n) << endl;
}