#include "Controller.h"
#include "OnpInterpreter.h"
#include <iostream>
#include <string>


int main()
{
	bool applicationStatus = true;
	
	Controller controller;

	controller.loadConstants();
	controller.loadFunctions();
	controller.loadOperators();

	while (applicationStatus)
	{
		try
		{
			applicationStatus = controller.getUserInput();
		}
		catch (std::exception &e)
		{
			std::cout << e.what() << std::endl;
		}
	}

	return 0;
}