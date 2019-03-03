#pragma once
#include <iostream>

class Validator
{
public:
	virtual bool validate(std::string expression) = 0;
};