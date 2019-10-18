#include "HW1_Array2D.h"

Array2D::Array2D(int size)
{
	m_size = size;

	m_array = new int* [m_size];
	for (int i = 0; i < m_size; ++i)
	{
		m_array[i] = new int[m_size];
	}

	for (int i = 0; i < m_size; ++i)
	{
		for (int j = 0; j < m_size; ++j)
		{
			m_array[i][j] = i * m_size + j + 1;
		}
	}
}

Array2D::~Array2D()
{
	if (m_array != NULL)
	{
		for (int i = 0; i < m_size; ++i)
		{
			delete[] m_array[i];
		}
	}

	m_size = 0;
}

ostream& operator<<(ostream& os, const Array2D& r)
{
	int max_digit_by_ten = 1;
	int max_digit = 1;

	// max digit check
	for (int i = 0; i < r.m_size; ++i)
	{
		for (int j = 0; j < r.m_size; ++j)
		{
			while (r.m_array[i][j] / (max_digit_by_ten * 10) != 0)
			{
				max_digit_by_ten *= 10;
				++max_digit;
			}
		}
	}

	for (int i = 0; i < r.m_size; ++i)
	{
		for (int j = 0; j < r.m_size; ++j)
		{
			os.width((std::streamsize)max_digit + 1);
			os << r.m_array[i][j];
		}
		os << '\n';
	}

	return os;
}

void Array2D::moveRight(int r, int dist)
{
	if (0 <= r && r <= m_size - 1)
	{
		for (int cnt = 0; cnt < dist; ++cnt)
		{
			for (int i = m_size - 2; i >= 0; --i)
			{
				swap(&m_array[r][i], &m_array[r][i + 1]);
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid r found, just doing nothing..." << endl;
	}
}

void Array2D::moveLeft(int r, int dist)
{
	if (0 <= r && r <= m_size - 1)
	{
		for (int cnt = 0; cnt < dist; ++cnt)
		{
			for (int i = 0; i < m_size - 1; ++i)
			{
				swap(&m_array[r][i], &m_array[r][i + 1]);
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid r found, just doing nothing..." << endl;
	}
}

void Array2D::moveUp(int c, int dist)
{
	if (0 <= c && c <= m_size - 1)
	{
		for (int cnt = 0; cnt < dist; ++cnt)
		{
			for (int i = 0; i < m_size - 1; ++i)
			{
				swap(&m_array[i][c], &m_array[i + 1][c]);
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid c found, just doing nothing..." << endl;
	}
}

void Array2D::moveDown(int c, int dist)
{
	if (0 <= c && c <= m_size - 1)
	{
		for (int cnt = 0; cnt < dist; ++cnt)
		{
			for (int i = m_size - 2; i >= 0; --i)
			{
				swap(&m_array[i][c], &m_array[i + 1][c]);
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid c found, just doing nothing..." << endl;
	}
}

void Array2D::moveUpRight(int d, int dist)
{
	if (1 <= d && d <= 2 * m_size - 3)
	{
		const int half_d = (2 * m_size - 3) / 2 + 1;

		if (d <= half_d)
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = d - 1; i >= 0; --i)
				{
					swap(&m_array[d - i][i], &m_array[d - i - 1][i + 1]);
				}
			}
		}
		else
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = m_size - 2; i >= d - m_size + 1; --i)
				{
					swap(&m_array[d - i][i], &m_array[d - i - 1][i + 1]);
				}
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid d found, just doing nothing..." << endl;
	}
}

void Array2D::moveDownLeft(int d, int dist)
{
	if (1 <= d && d <= 2 * m_size - 3)
	{
		const int half_d = (2 * m_size - 3) / 2 + 1;

		if (d <= half_d)
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = 0; i < d; ++i)
				{
					swap(&m_array[d - i][i], &m_array[d - i - 1][i + 1]);
				}
			}
		}
		else
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = d - m_size + 1; i < m_size - 1; ++i)
				{
					swap(&m_array[d - i][i], &m_array[d - i - 1][i + 1]);
				}
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid d found, just doing nothing..." << endl;
	}
}

void Array2D::moveUpLeft(int d, int dist)
{
	if (1 <= d && d <= 2 * m_size - 3)
	{
		const int half_d = (2 * m_size - 3) / 2 + 1;

		if (d <= half_d)
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = 0; i < d; ++i)
				{
					swap(&m_array[m_size - d - 1 + i][i], &m_array[m_size - d + i][i + 1]);
				}
			}
		}
		else
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = d - m_size + 1; i < m_size - 1; ++i)
				{
					swap(&m_array[i - d + m_size - 1][i], &m_array[i - d + m_size][i + 1]);
				}
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid d found, just doing nothing..." << endl;
	}
}

void Array2D::moveDownRight(int d, int dist)
{
	if (1 <= d && d <= 2 * m_size - 3)
	{
		const int half_d = (2 * m_size - 3) / 2 + 1;

		if (d <= half_d)
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = d - 1; i >= 0; --i)
				{
					swap(&m_array[m_size - d - 1 + i][i], &m_array[m_size - d + i][i + 1]);
				}
			}
		}
		else
		{
			for (int cnt = 0; cnt < dist; ++cnt)
			{
				for (int i = m_size - 2; i >= d - m_size + 1; --i)
				{
					swap(&m_array[i - d + m_size - 1][i], &m_array[i - d + m_size][i + 1]);
				}
			}
		}
	}
	else
	{
		cout << "[Array2D] Invalid d found, just doing nothing..." << endl;
	}
}

void Array2D::swap(int* a, int* b)
{
	int temp = *a;
	*a = *b;
	*b = temp;
}