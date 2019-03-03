#include "Controller.h"
#include <string>
#include <sstream>
#include <fstream>

bool Controller::showParameters = true;

int Controller::displayText()
{
	std::cout << "\nKALKULATOR\n";
	std::cout << "------------------------------\n";
	if (showParameters)
	{
		std::cout << "Dostepne stale:\n";
		Constant::showConstants();
		std::cout << "Dostepne funkcje:\n";
		Function::showFunctions();
		std::cout << "Dostepne operatory:\n";
		Operator::showOperators();
	}

	std::cout << "1. Oblicz wyrazenie podane z klawiatury\n";
	std::cout << "2. Oblicz wyrazenie z pliku\n";


	std::cout << "3. Dodaj stala\n";
	if (showParameters)
		std::cout << "4. Wylacz pokazywanie stalych, funkcji, operatorow\n";
	else
		std::cout << "4. Wlacz pokazywanie stalych, funkcji, operatorow\n";
	std::cout << "5. Wyjscie\n";
	int choice;
	std::string str;

	std::getline(std::cin, str);
	std::stringstream linestream(str);
	linestream >> choice;

	return choice;
}

void Controller::calculateFromKeyboard()
{
	std::string expression;
	std::cout << "Podaj wyrazenie do obliczenia:\n";
	std::getline(std::cin, expression);
	double result = interpreter.calculate(expression);
}

void Controller::addConst()
{
	std::string expression;
	std::string value;
	std::cout << "Podaj nazwe stalej, nazwa musi zaczynac sie od du¿ej litery: 'M' i zawieraæ w sumie 4 litery:\n";
	std::getline(std::cin, expression);
	std::cout << "Podaj wartosc stalej:\n";
	std::getline(std::cin, value);
	Constant::addConst(expression, value);
}

void Controller::calculateFromFile()
{
	std::string fileName;
	std::cout << "Podaj nazwe pliku:\n";
	std::getline(std::cin, fileName);
	std::string expression = OnpFileHandler::getExpressionFromFile(fileName);
	double result = interpreter.calculate(expression);
}


bool Controller::handleUserChoice(int choice)
{
	enum Options
	{
		calculateExpressionFromKeyboard = 1, calculateExpressionFromFile, addConstant, changeDisplay,
		exit
	};
	
	switch (choice)
	{
	case calculateExpressionFromKeyboard:
		calculateFromKeyboard(); break;
	case calculateExpressionFromFile:
		calculateFromFile(); break;
	case addConstant:
		addConst(); break;
	case changeDisplay:
		showParameters = !showParameters;  break;
	case exit:
		return false;
	}
	
	return true;
}

Controller::Controller()
{

}

bool Controller::getUserInput()
{
	int choice;
	choice = displayText();
	return handleUserChoice(choice);
}

void Controller::loadConstants()
{
	Constant::initConstants();
}

void Controller::loadFunctions()
{
	Function::initFunctions();
}

void Controller::loadOperators()
{
	Operator::initOperators();
}

