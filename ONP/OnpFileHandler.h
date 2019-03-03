#pragma once
#include <iostream>
#include <map>

class OnpFileHandler
{
private:
	static const std::string NAME_OF_CONSTANTS_FILE;
public:
	static std::string getExpressionFromFile(std::string fileName);
	static void addConstToFile(std::string expression);
	static void loadConstantsFromFile(std::map<std::string, std::string> &constants);
};