#pragma once
#include "Function.h"
#include "Constant.h"
#include "OnpInterpreter.h"
#include "OnpFileHandler.h"
#include "Operator.h"
#include <map>
#include <iostream>

class Controller
{
private:
	void calculateFromKeyboard();
	void calculateFromFile();
	void addConst();
	int displayText();
	bool handleUserChoice(int choice);
	OnpInterpreter interpreter;
public:
	Controller();
	static bool showParameters;
	bool getUserInput();
	void loadConstants();
	void loadFunctions();
	void loadOperators();
};