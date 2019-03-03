#include "BracketValidator.h"
#include "Stack.h"

bool areParanthesisBalanced(std::string expr)
{
	Stack<char> s;
	char x;
	
	for (int i = 0; i < expr.length(); i++)
	{
		if (expr[i] == '(')
		{
			s.push(expr[i]);
			continue;
		}

		if (expr[i] == ')' && s.empty())
			return false;
		
		if (expr[i] == ')')
		{
			x = s.pop();
		}
	}

	return (s.empty());
}

bool BracketValidator::validate(std::string expression)
{
	return areParanthesisBalanced(expression);
}
