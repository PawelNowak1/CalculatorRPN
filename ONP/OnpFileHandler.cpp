#include "OnpFileHandler.h"
#include <fstream>
#include <sstream>
#include <string>

const std::string OnpFileHandler::NAME_OF_CONSTANTS_FILE = "constants.txt";

std::string OnpFileHandler::getExpressionFromFile(std::string fileName)
{
	std::ifstream inFile(fileName);
	if (!inFile.good() || !inFile.is_open())
		return "";
	std::string a;
	inFile >> a;
	inFile.close();
	return a;
}

void OnpFileHandler::addConstToFile(std::string expression)
{
	std::ofstream outfile;

	outfile.open(NAME_OF_CONSTANTS_FILE, std::ios_base::app);
	outfile << "\n" << expression;
	outfile.close();
}

void OnpFileHandler::loadConstantsFromFile(std::map<std::string, std::string>& constants)
{
	std::ifstream infile(NAME_OF_CONSTANTS_FILE);
	
	std::string a, b;
	while (infile >> a >> b)
	{
		constants.insert(std::pair<std::string, std::string>(a, b));
	}
	infile.close();
}
