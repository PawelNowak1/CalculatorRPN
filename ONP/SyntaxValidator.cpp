#include "SyntaxValidator.h"

bool SyntaxValidator::validate(std::string expression)
{
	if(expression.length() <= 0)
		return false;
	return true;
}
