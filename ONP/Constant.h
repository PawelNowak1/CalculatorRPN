#pragma once
#include <iostream>
#include <map>

class Constant
{
private:
	static const int numberOfLettersInAConst = 4;
	static const char startLetterConst = 'M';
	static bool verifyConst(std::string expr);
public:
	Constant() = default;
	static std::map<std::string, std::string> constants;
	static void showConstants();
	static void initConstants();
	static char getStartLetterConst();
	static int getNumberOfLettersInAConst();
	static void addConst(std::string expression, std::string value);
};