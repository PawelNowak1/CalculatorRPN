#include "Constant.h"
#include "OnpFileHandler.h"
#include <string>
#include <vector>
#include <algorithm>

std::map<std::string, std::string> Constant::constants;

void Constant::showConstants()
{
	for (auto const& x : constants)
	{
		std::cout << "\t" << x.first  // string (key)
			<< ":\t"
			<< x.second // string's value 
			<< std::endl;
	}
}

void Constant::initConstants()
{
	OnpFileHandler::loadConstantsFromFile(constants);
}

char Constant::getStartLetterConst()
{
	return startLetterConst;
}

int Constant::getNumberOfLettersInAConst()
{
	return numberOfLettersInAConst;
}


bool Constant::verifyConst(std::string expression)
{
	return (expression[0] == startLetterConst && numberOfLettersInAConst == expression.length());
}

void Constant::addConst(std::string expression, std::string value)
{
	if (!verifyConst(expression))
	{
		std::cout << "niepoprawna nazwa stalej\n";
		return;
	}

	std::vector<std::string> v;
	for (std::map<std::string, std::string>::iterator it = constants.begin(); it != constants.end(); ++it) {
		if (expression == it->first)
		{
			std::cout << "Stala o takiej nazwie juz istnieje\n";
			return;
		}
	}
	std::replace(value.begin(), value.end(), ',', '.');
	constants.insert(std::pair<std::string, std::string>(expression, value));
	OnpFileHandler::addConstToFile(expression + " " + value);
}