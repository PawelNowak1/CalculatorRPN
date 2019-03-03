#include "Function.h"
#include "Stack.h"
#include <math.h>
#include <string>

Stack<Function> Function::functions;

double _sin(Stack<double> &args)
{
	return sin(args[0]);
}

double _abs(Stack<double> &args)
{
	return abs(args[0]);
}

double _max(Stack<double> &args)
{
	double max = args[0];
	if (max < args[1])
		max = args[1];
	if (max > args[2])
		return max;
	return args[2];
}

double _cos(Stack<double> &args)
{
	return cos(args[0]);
}

double _tan(Stack<double> &args)
{
	return tan(args[0]);
}

double _ceil(Stack<double> &args)
{
	return ceil(args[0]);
}

double _exp(Stack<double> &args)
{
	return exp(args[0]);
}

double _floor(Stack<double> &args)
{
	return floor(args[0]);
}

double _ln(Stack<double> &args)
{
	return log(args[0]);
}

double _log10(Stack<double> &args)
{
	return log10(args[0]);
}

double _sqrt(Stack<double> &args)
{
	return sqrt(args[0]);
}

double _min(Stack<double> &args)
{
	double min = args[0];
	if (min > args[1])
		min = args[1];
	return min;
}

void Function::showFunctions()
{
	int size = functions.getSize();
	for (int i = 0; i < size; i++)
	{
		std::cout << "\t" << functions[i].name << "\tIlosc argumentow funkcji: " << functions[i].numberOfArgs << "\n";
	}
}
void Function::initFunctions()
{
	functions.push(Function("max", _max, 3));
	functions.push(Function("min", _min, 2));
	functions.push(Function("sin", _sin, 1));
	functions.push(Function("abs", _abs, 1));
	functions.push(Function("cos", _cos, 1));
	functions.push(Function("tan", _tan, 1));
	functions.push(Function("ceil", _ceil, 1));
	functions.push(Function("floor", _floor, 1));
	functions.push(Function("ln", _ln, 1));
	functions.push(Function("log10", _log10, 1));
	functions.push(Function("sqrt", _sqrt, 1));
	functions.push(Function("exp", _exp, 1));
}

int Function::getNumberOfArgs() const
{
	return numberOfArgs;
}

Function::Function(std::string _name, double(*_calculate)(Stack<double>&), int _args)
{
	calculate = _calculate;
	name = _name;
	numberOfArgs = _args;
}
