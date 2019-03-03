#pragma once
#include <iostream>
#include <vector>
#include "Operator.h"
#include "Stack.h"
#include "Constant.h"
#include "Function.h"

class OnpInterpreter
{
private:
	std::string expr;
	double result;
	void validate(std::string expression);
	void parseExpressionToOnp(std::string expression, Stack<std::string> &output);
public:
	OnpInterpreter();
	OnpInterpreter(std::string _expr);
	double calculate(std::string expression);
	double operator=(const OnpInterpreter& onp);
	friend std::ostream& operator<< (std::ostream& stream, const OnpInterpreter& onp);
};