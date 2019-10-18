#include "HW1_NaryBigNum.h"

int chrAsInt(int base, char c)
{
	if (base <= 10)
	{
		if ('0' <= c && c <= '9')
			return c - '0';
	}
	else if (11 <= base && base <= 36)
	{
		if ('0' <= c && c <= '9')
			return c - '0';
		else if ('A' <= c && c <= 'Z')
			return c - 'A' + 10;
	}

	return 0;
}

char intAsChr(int base, int n)
{
	if (base <= 10)
	{
		if (0 <= n && n <= 9)
			return n + '0';
	}
	else if (11 <= base && base <= 36)
	{
		if (0 <= n && n <= 9)
			return n + '0';
		else if (10 <= n && n <= 35)
			return n + 'A' - 10;
	}

	return '0';
}

NaryBigNum::NaryBigNum()
{
	number = NULL;
	size = 0;
	base = 10;
}

// Assumes it only takes positive integers
NaryBigNum::NaryBigNum(int n, string num)
{
	if (num == "") // In case that real size of num is 0, use default settings
	{
		number = NULL;
		size = 0;
		base = n;
	}
	else
	{
		int actual_starting_point = 0;
		unsigned int leftmost_zero_cnt = 0;

		// If base is not between 2 and 36, store base as 10
		if (n < 2 || n > 36)
			base = 10;
		else
			base = n;

		/* Convert num into appropriate form */
		for (unsigned int i = 0; i < num.length(); ++i)
		{
			// Check lowercase, and change 'em to uppercase
			if ('a' <= num[i] && num[i] <= 'z')
			{
				num[i] = toupper(num[i]);
			}
			
			// 2 <= base <= 10
			if (base <= 10)
			{
				if (!('0' <= num[i] && num[i] <= base + 47))
				{
					num[i] = '0';
				}
			}
			// 11 <= base <= 36
			else
			{
				if (!(('0' <= num[i] && num[i] <= '9') || ('A' <= num[i] && num[i] <= base + 54)))
				{
					num[i] = '0';
				}
			}
		}

		// Getting real size of number, considering zeros
		while (leftmost_zero_cnt < num.length() - 1)
		{
			if (num[leftmost_zero_cnt] != '0')
				break;

			++leftmost_zero_cnt;
		}

		size = num.length() - leftmost_zero_cnt;

		// Copies final result form to number
		number = new char[size + 1];
		strcpy_s(number, size + 1, num.substr(leftmost_zero_cnt).c_str());
	}
}

NaryBigNum::NaryBigNum(const NaryBigNum& nbn)
{
	size = nbn.size;
	base = nbn.base;
	number = new char[size + 1];
	strcpy_s(number, size + 1, nbn.number);
}

NaryBigNum::~NaryBigNum()
{
	if (number != NULL)
		delete[] number;
}

NaryBigNum NaryBigNum::operator+(const NaryBigNum& nbn)
{
	if (base != nbn.base)
	{
		cout << "[NaryBigNum] Two bases differ, unable to add" << endl;
		cout << "[NaryBigNum] Returning empty NaryBigNum as a result" << endl;
		return NaryBigNum();
	}
	else
	{
		string res = "";

		if (size < nbn.size)
		{
			int res_add;
			int i;
			bool existsCarry = false;

			for (i = 0; i < size; ++i)
			{
				res_add = chrAsInt(base, number[size - i - 1]) + chrAsInt(base, nbn.number[nbn.size - i - 1]) + (existsCarry ? 1 : 0);

				existsCarry = res_add / base == 1;
				res_add %= base;

				res.insert(0, 1, intAsChr(base, res_add));
			}

			for (; i < nbn.size; ++i)
			{
				res_add = chrAsInt(base, nbn.number[nbn.size - i - 1]) + (existsCarry ? 1 : 0);

				existsCarry = res_add / base == 1;
				res_add %= base;

				res.insert(0, 1, intAsChr(base, res_add));
			}

			if (existsCarry)
				res.insert(0, 1, '1');
		}
		else
		{
			int res_add;
			int i;
			bool existsCarry = false;

			for (i = 0; i < nbn.size; ++i)
			{
				res_add = chrAsInt(base, number[size - i - 1]) + chrAsInt(base, nbn.number[nbn.size - i - 1]) + (existsCarry ? 1 : 0);

				existsCarry = res_add / base == 1;
				res_add %= base;

				res.insert(0, 1, intAsChr(base, res_add));
			}

			for (; i < size; ++i)
			{
				res_add = chrAsInt(base, number[size - i - 1]) + (existsCarry ? 1 : 0);

				existsCarry = res_add / base == 1;
				res_add %= base;

				res.insert(0, 1, intAsChr(base, res_add));
			}

			if (existsCarry)
				res.insert(0, 1, '1');
		}

		return NaryBigNum(base, res);
	}
}

NaryBigNum& NaryBigNum::operator=(const NaryBigNum& nbn)
{
	size = nbn.size;
	base = nbn.base;

	if (number != NULL)
		delete[] number;

	number = new char[size + 1];
	strcpy_s(number, size + 1, nbn.number);

	return *this;
}

NaryBigNum NaryBigNum::operator*(const NaryBigNum& nbn)
{
	if (base != nbn.base)
	{
		cout << "[NaryBigNum] Two bases differ, unable to multiply" << endl;
		cout << "[NaryBigNum] Returning empty NaryBigNum as a result" << endl;
		return NaryBigNum();
	}
	else
	{
		NaryBigNum res_obj(base, string("0"));

		int i, j;

		for (i = 0; i < size; ++i)
		{
			string res_multiply_part = "";
			int carry = 0;

			for (j = 0; j < nbn.size; ++j)
			{
				int res_of_temp = chrAsInt(base, nbn.number[nbn.size - j - 1]) * chrAsInt(base, number[size - i - 1]) + carry;

				carry = res_of_temp / base;
				res_of_temp %= base;

				res_multiply_part.insert(0, 1, intAsChr(base, res_of_temp));
			}

			if (carry)
			{
				res_multiply_part.insert(0, 1, intAsChr(base, carry));
			}

			res_obj = res_obj + NaryBigNum(base, res_multiply_part.insert(res_multiply_part.length(), i, '0'));
		}

		return res_obj;
	}
}

ostream& operator<<(ostream& os, const NaryBigNum& nbn)
{
	if (nbn.number == NULL)
		os << "NULL (" << nbn.base << ")";
	else
		os << nbn.number << " (" << nbn.base << ")";
	
	return os;
}