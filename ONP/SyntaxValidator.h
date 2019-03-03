#pragma once
#include "Validator.h"

class SyntaxValidator : public Validator
{
public:
	static std::string name;
	bool validate(std::string expression) override;
};