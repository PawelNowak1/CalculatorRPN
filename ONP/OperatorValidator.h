#pragma once
#include "Validator.h"

class OperatorValidator : public Validator
{
public:
	static std::string name;
	bool validate(std::string expression) override;
};