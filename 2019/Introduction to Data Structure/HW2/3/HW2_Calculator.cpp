#include "HW2_Calculator.h"
#include "HW2_Stack.h"

bool isOperand(char c)
{
	if ('0' <= c && c <= '9')
		return true;
	
	return false;
}

Calculator::Calculator(string str)
{
	exp_infix = str;

	w_add = 1;
	w_sub = 1;
	w_mult = 2;
	w_div = 2;
	w_pow = 3;
}

void Calculator::setInfixExp(string str)
{
	exp_infix = str;
}

void Calculator::setWeight(char op, int w)
{
	switch (op)
	{
	case '+':
		w_add = w;
		break;
	case '-':
		w_sub = w;
		break;
	case '*':
		w_mult = w;
		break;
	case '/':
		w_div = w;
		break;
	case '^':
		w_pow = w;
		break;
	}
}

int Calculator::getWeight(char op) const
{
	switch (op)
	{
	case '+':
		return w_add;
	case '-':
		return w_sub;
	case '*':
		return w_mult;
	case '/':
		return w_div;
	case '^':
		return w_pow;
	default:
		return -1;
	}
}

string Calculator::getPostfixExp() const
{
	Stack<char> stack_op;
	string exp_postfix = "";

	for (unsigned int i = 0; i < exp_infix.length(); ++i)
	{
		if (isOperand(exp_infix[i]))
		{
			exp_postfix += exp_infix[i];
		}
		else if (stack_op.isEmpty())
		{
			stack_op.push(exp_infix[i]);
		}
		else if (exp_infix[i] == '(')
		{
			stack_op.push('(');
		}
		else if (exp_infix[i] == ')')
		{
			char tmp_op = stack_op.pop();

			while (tmp_op != '(')
			{
				exp_postfix += tmp_op;
				tmp_op = stack_op.pop();
			}
		}
		else if (stack_op.getTop() == '(')
		{
			stack_op.push(exp_infix[i]);
		}
		else if (getWeight(exp_infix[i]) > getWeight(stack_op.getTop()))
		{
			stack_op.push(exp_infix[i]);
		}
		else if (getWeight(exp_infix[i]) <= getWeight(stack_op.getTop()))
		{
			do
			{
				exp_postfix += stack_op.pop();

				if (stack_op.isEmpty() || stack_op.getTop() == '(')
					break;

			} while (getWeight(stack_op.getTop()) >= getWeight(exp_infix[i]));

			stack_op.push(exp_infix[i]);
		}
	}

	while (stack_op.getSize() > 0)
	{
		exp_postfix += stack_op.pop();
	}

	return exp_postfix;
}

int Calculator::calcTwoOperands(int operand1, int operand2, char op) const
{
	switch (op)
	{
	case '+':
		return operand1 + operand2;
	case '-':
		return operand1 - operand2;
	case '*':
		return operand1 * operand2;
	case '/':
		return operand1 / operand2;
	case '^':
		int pow_res = 1;

		for (int i = 0; i < operand2; ++i)
		{
			pow_res *= operand1;
		}

		return pow_res;
	}

	return -1;
}

int Calculator::calculate()
{
	string exp_postfix = getPostfixExp();
	Stack<int> stack_operand;
	
	for (unsigned int i = 0; i < exp_postfix.length(); ++i)
	{
		if (isOperand(exp_postfix[i]))
		{
			stack_operand.push(exp_postfix[i] - '0');
		}
		else
		{
			// Stack memory에 함수 인자는 뒤에서부터 들어간다(함수 호출 규약, 어셈블리 디버거로 확인 가능).
			// 따라서, Power 연산에서 Operand2에 Stack에서 위에 있는 수가 들어가게 됨!
			stack_operand.push(calcTwoOperands(stack_operand.pop(), stack_operand.pop(), exp_postfix[i])); 
		}
	}

	return stack_operand.pop();
}