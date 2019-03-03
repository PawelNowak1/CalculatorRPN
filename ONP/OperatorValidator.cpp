#include "OperatorValidator.h"

bool isOperator(char x)
{
	int numberOfOperators = 5;
	char operators[] = { '*', '/', '+', '-', '^' };
	for(int i = 0; i < numberOfOperators; i++)
	{
		if (x == operators[i])
			return true;
	}
	return false;
}

bool OperatorValidator::validate(std::string expression)
{
	int numberOfOperators = 5;
	char operators[] = { '*', '/', '+', '-', '^' };
	
	for (int i = 0; i < numberOfOperators; i++)
	{
		if (expression[0] == operators[i] || expression[expression.length() - 1] == operators[i])
			return false;
	}

	for (int i = 0; i < expression.length(); i++)
	{
		if (isOperator(expression[i]) && isOperator(expression[i + 1]))
			return false;
	}
	return true;
}
