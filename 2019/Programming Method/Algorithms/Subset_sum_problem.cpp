#include <iostream>

using namespace std;

bool isExistSubset2(int* set, int r, int sum)
{
	if (sum < 0)
		return false;
	if (sum == 0)
		return true;
	if (r == 0)
		return set[0] == sum;

	return isExistSubset2(set, r - 1, sum) || isExistSubset2(set, r - 1, sum - set[r]);
}

bool isExistSubset(int *set, int r, int sum)
{
	bool **res = new bool*[r + 1];
	for (int k = 0; k <= r; k++)
	{
		res[k] = new bool[sum + 1];
	}

	for (int j = 1; j <= sum; j++)
		res[0][j] = (set[0] == j);
	for (int i = 0; i <= r; i++)
		res[i][0] = true;

	for (int i = 1; i <= r; i++)
	{
		for (int j = 1; j <= sum; j++)
		{
			if (j < set[i])
				res[i][j] = res[i - 1][j];
			else
				res[i][j] = res[i - 1][j] + res[i - 1][j - set[i]];
		}
	}

	bool result = res[r][sum];
	for (int i = 0; i <= r; i++)
	{
		delete[] res[i];
	}
	delete[] res;

	return result;
}

int main()
{
	int *set;
	int n;
	int sum;

	cout << "n: ";
	cin >> n;
	set = new int[n];
	cout << "array: ";
	for (int i = 0; i < n; i++)
		cin >> set[i];
	cout << "sum: ";
	cin >> sum;

	if (isExistSubset(set, n - 1, sum))
		cout << "Output: True" << endl;
	else
		cout << "Output: False" << endl;

	delete[] set;
	return 0;
}