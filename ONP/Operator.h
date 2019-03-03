#pragma once
#include "Stack.h"
#include <iostream>

typedef enum direction
{
	left,
	right
};


class Operator
{
public:
	Operator(std::string _name, int _precendence, direction _dir, double(*_calculate)(double, double));
	Operator();
	static void showOperators();
	static Stack<Operator> operators;
	static void initOperators();
	std::string name;
	int precendence;
	direction dir;
	double(*calculate)(double, double);
};