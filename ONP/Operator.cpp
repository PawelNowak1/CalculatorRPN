#include "Operator.h"
#include <string>

Stack<Operator> Operator::operators;

Operator::Operator(std::string _name, int _precendence, direction _dir, double(*_calculate)(double, double))
{
	name = _name;
	precendence = _precendence;
	dir = _dir;
	calculate = _calculate;
}

Operator::Operator()
{

}

void Operator::showOperators()
{
	int size = operators.getSize();
	std::cout << "\t";
	for (int i = 0; i < size; i++)
	{
		std::cout << operators[i].name << " ";
	}
	std::cout << "\n";
}

double add(double arg1, double arg2)
{
	return arg1 + arg2;
}

double substract(double arg1, double arg2)
{
	return arg1 - arg2;
}

double multiply(double arg1, double arg2)
{
	return arg1 * arg2;
}

double divide(double arg1, double arg2)
{
	return arg1 / arg2;
}

double power(double arg1, double arg2)
{
	return pow(arg1, arg2);
}

void Operator::initOperators()
{
	operators.push(Operator("+", 1, (direction)left, add));
	operators.push(Operator("-", 1, (direction)left, substract));
	operators.push(Operator("*", 2, (direction)left, multiply));
	operators.push(Operator("/", 2, (direction)left, divide));
	operators.push(Operator("^", 3, (direction)right, power));
}