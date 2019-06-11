#include <iostream>
#include <string>

using namespace std;

inline int min(int a, int b)
{
	return a < b ? a : b;
}

int main()
{
	int n;
	int *a1; int *a2;
	int *t1; int *t2;
	int e1, e2;
	int x1, x2;
	string s1 = ""; string s2 = "";
	int f1Last; int f2Last;

	cin >> n;

	a1 = new int[n];
	a2 = new int[n];
	t1 = new int[n - 1];
	t2 = new int[n - 1];

	cin >> e1;
	for (int i = 0; i < n; i++)
	{
		cin >> a1[i];
	}
	cin >> x1;

	cin >> e2;
	for (int i = 0; i < n; i++)
	{
		cin >> a2[i];
	}
	cin >> x2;

	for (int i = 0; i < n - 1; i++)
	{
		cin >> t1[i];
	}

	for (int i = 0; i < n - 1; i++)
	{
		cin >> t2[i];
	}

	f1Last = e1 + a1[0];
	f2Last = e2 + a2[0];
	s1.append("1 ");
	s2.append("2 ");

	for (int i = 1; i < n; i++)
	{
		int tmpLast = f1Last; 
		string tmpS1 = "";
		tmpS1.append(s1);
		
		if (f1Last <= f2Last + t2[i - 1])
		{
			f1Last = f1Last + a1[i];
			s1.append("1 ");
		}
		else
		{
			f1Last = f2Last + t2[i - 1] + a1[i];
			s1 = "";
			s1.append(s2);
			s1.append("1 ");
		}

		if (f2Last <= tmpLast + t1[i - 1])
		{
			f2Last = f2Last + a2[i];
			s2.append("2 ");
		}
		else
		{
			f2Last = tmpLast + t1[i - 1] + a2[i];
			s2 = "";
			s2.append(tmpS1);
			s2.append("2 ");
		}
	}

	f1Last += x1;
	f2Last += x2;

	if (f1Last < f2Last)
	{
		cout << "Minimum time is: " << f1Last << endl;
		cout << "Optimal Path is: " << s1 << endl;
	}
	else
	{
		cout << "Minimum time is: " << f2Last << endl;
		cout << "Optimal Path is: " << s2 << endl;
	}

	delete[] a1; delete[] a2;
	delete[] t1; delete[] t2;
}