#include <iostream>

using namespace std;

int coin(int *p, int &n, int &k)
{
	int **r = new int*[n];
	
	for (int i = 0; i < n; i++)
	{
		r[i] = new int[k + 1];
	}

	for (int i = 0; i < n; i++)
	{
		r[i][0] = 1;
	}

	for (int j = 1; j <= k; j++)
	{
		if (j % p[0] == 0)
			r[0][j] = 1;
		else
			r[0][j] = 0;
	}

	for (int i = 1; i < n; i++)
	{
		for (int j = 1; j <= k; j++)
		{
			if (j < p[i])
				r[i][j] = r[i - 1][j];
			else
				r[i][j] = r[i][j - p[i]] + r[i - 1][j];
		}
	}
	
	int tmp = r[n - 1][k];
	for (int i = 0; i < n; i++)
	{
		delete[] r[i];
	}
	delete[] r;
	return tmp;
}

int main()
{
	int n, k;
	int *p;

	cin >> n >> k;
	p = new int[n];

	for (int i = 0; i < n; i++)
	{
		cin >> p[i];
	}

	cout << coin(p, n, k) << endl;

	delete[] p;
	return 0;
}