#pragma once
#include "Stack.h"
#include <iostream>

class Function
{
private:
	int numberOfArgs;

public:
	static Stack<Function> functions;
	Function() = default;
	Function(std::string _name, double(*_calculate)(Stack<double>&), int args);
	static void showFunctions();
	static void initFunctions();
	std::string name;
	int getNumberOfArgs() const;
	double(*calculate)(Stack<double>&);
};