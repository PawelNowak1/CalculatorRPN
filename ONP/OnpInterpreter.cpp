#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include "Stack.h"
#include "OnpInterpreter.h"
#include "Constant.h"
#include "BracketValidator.h"
#include "OperatorValidator.h"
#include "SyntaxValidator.h"

bool isInteger(std::string token)
{
	return (token[0] >= '0' && token[0] <= '9') || token[0] == '.';
}

bool isAFunction(std::string token)
{
	return ((token[0] >= 'A' && token[0] <= 'Z' && token[0] != Constant::getStartLetterConst()) || (token[0] >= 'a' && token[0] <= 'z'));
}

bool isAnOperator(std::string token, Stack<Operator> &operators)
{
	int size = operators.getSize();
	for (int i = 0; i < size; i++)
	{
		if (operators[i].name == token)
			return true;
	}
	return false;
}

bool isAnOperatorAndGreaterPrecedence(std::string token, std::string a, Stack<Operator> &operators)
{
	if (!isAnOperator(a, operators))
		return false;

	int precedence1, precedence2;
	int size = operators.getSize();

	for (int i = 0; i < size; i++)
	{
		if (operators[i].name == token)
			precedence1 = operators[i].precendence;
		if (operators[i].name == a)
			precedence2 = operators[i].precendence;
	}
	return precedence2 > precedence1;
}

bool equalPrecedenceAndLeftAssociative(std::string token, std::string a, Stack<Operator> &operators)
{
	if (!isAnOperator(a, operators))
		return false;

	int precedence1, precedence2;
	int size = operators.getSize();
	direction dir = (direction)right;

	for (int i = 0; i < size; i++)
	{
		if (operators[i].name == token)
			precedence1 = operators[i].precendence;
		if (operators[i].name == a)
		{
			precedence2 = operators[i].precendence;
			dir = (direction)operators[i].dir;
		}
	}
	return (precedence2 == precedence1) && dir == (direction)left;
}

bool isAConstant(std::string token)
{
	return (token[0] == Constant::getStartLetterConst());
}

void handleInteger(int& i, std::string in, Stack<std::string> & output, std::string token)
{
	i++;
	std::string temp;
	temp = in[i];
	while (isInteger(temp) || temp == ".")
	{
		i++;
		token = token + temp;
		temp = in[i];
	}
	i--;
	output.push(token);
}

bool isFunctionValid(std::string functionName)
{
	for (int j = 0; j < Function::functions.getSize(); j++)
	{
		if (Function::functions[j].name == functionName)
		{
			return true;
		}
	}
	return false;
}

void handleFunction(int& i, std::string in, Stack<std::string> & output, std::string token)
{
	i++;
	std::string temp;
	temp = in[i];
	while (temp != "(")
	{
		if (i >= in.length())
			throw std::exception("Brack '(' po funkcji");
		i++;
		token = token + temp;
		temp = in[i];
	}
	i--;

	if (isFunctionValid(token))
		output.push(token);
	else
		throw std::exception("Nierozpoznana nazwa funkcji.");
}

void changeConstantsWithNumbers(std::string &in, std::map<std::string, std::string> constants)
{
	int length = in.length();
	for (int i = 0; i < length; i++)
	{
		if (in[i] == 'M')
		{
			std::string temp = in.substr(i, Constant::getNumberOfLettersInAConst());
			if (constants.find(temp) == constants.end())
				throw std::exception("Nie rozpoznano stalej.");
			in.replace(i, Constant::getNumberOfLettersInAConst(), constants.find(temp)->second);
			length = in.length();
		}
	}
}

void removeSpaces(std::string &in)
{
	std::string::iterator end_pos = std::remove(in.begin(), in.end(), ' ');
	in.erase(end_pos, in.end());
}

void replaceBrackets(std::string &in)
{
	std::replace(in.begin(), in.end(), '{', '(');
	std::replace(in.begin(), in.end(), '[', '(');
	std::replace(in.begin(), in.end(), '}', ')');
	std::replace(in.begin(), in.end(), ']', ')');
}

void handleMinuses(std::string &in)
{
	if (in[0] == '-')
		in = "0" + in;

	std::regex reg("[(][-]");
	in = std::regex_replace(in, reg, "(0-");

}

void OnpInterpreter::parseExpressionToOnp(std::string in, Stack<std::string> &output)
{
	Stack<Operator> &operators = Operator::operators;

	Stack<std::string> stack;
	std::string token;

	removeSpaces(in);
	changeConstantsWithNumbers(in, Constant::constants);
	replaceBrackets(in);
	handleMinuses(in);

	for (int i = 0; i < in.length(); i++)
	{

		token = in[i];
		if (isInteger(token))
			handleInteger(i, in, output, token);
		else if (isAFunction(token))
			handleFunction(i, in, stack, token);
		else if (isAnOperator(token, operators))
		{
			while (!stack.empty() && ( isAFunction(stack.peek()) || isAnOperatorAndGreaterPrecedence(token, stack.peek(), operators) || equalPrecedenceAndLeftAssociative(token, stack.peek(), operators)) && stack.peek()[0] != '(')
			{
				output.push(stack.pop());
			}
			stack.push(token);
		}
		else if (token[0] == '(')
			stack.push(token);
		else if (token[0] == ',')
		{
			while (stack.peek()[0] != '(')
			{
				output.push(stack.pop());
			}
		}
		else if (token[0] == ')')
		{
			while (stack.peek()[0] != '(')
			{
				output.push(stack.pop());
			}
			stack.pop(); // LEFT BRACKET
		}
	}

	while (stack.getSize() > 0)
	{
		//mismatched is a bracket
		output.push(stack.pop());
	}
}

OnpInterpreter::OnpInterpreter()
{
}

OnpInterpreter::OnpInterpreter(std::string _expr)
{
	expr = _expr;
}

double calculateOperators(double a, double b, Stack<Operator> &operators, std::string token)
{
	int size = operators.getSize();
	for (int i = 0; i < size; i++)
	{
		if (operators[i].name == token)
		{
			return operators[i].calculate(b, a);
			break;
		}
	}
}

double calculateFunction(Stack<double> &stack, Stack<Function> &functions, std::string token)
{

	int size = functions.getSize();
	for (int i = 0; i < size; i++)
	{
		if (functions[i].name == token)
		{
			int numberOfArgs = functions[i].getNumberOfArgs();
			Stack<double> temp;
			for (int k = 0; k < numberOfArgs; k++)
			{
				temp.push(stack.pop());
			}

			return functions[i].calculate(temp);
		}
	}
}

double calculatePostFix(Stack<std::string> &symbols)
{

	Stack<Operator> &operators = Operator::operators;
	Stack<Function> &functions = Function::functions;
	Stack<double> stack;
	while (!symbols.empty())
	{
		std::string token = symbols.popHead();
		if ((token[0] >= '0' && token[0] <= '9') || token[0] == '.')
			stack.push(std::stod(token));
		else if (isAnOperator(token, operators))
		{
			double a = stack.pop();
			double b = stack.pop();
			stack.push(calculateOperators(a, b, operators, token));
		}
		else if (isAFunction(token))
		{
			stack.push(calculateFunction(stack, functions, token));
		}
	}

	if (stack.getSize() > 1)
		throw std::exception("Blad na stosie");
	return stack.pop();
}

void OnpInterpreter::validate(std::string expression)
{
	BracketValidator bracketValidator;
	OperatorValidator operatorValidator;
	SyntaxValidator syntaxValidator;
	if (!syntaxValidator.validate(expression))
		throw std::exception("blad w skladni");
	if (!bracketValidator.validate(expression))
		throw std::exception("zle nawiasy");
	if (!operatorValidator.validate(expression))
		throw std::exception("Bledne wykorzystanie operatorow");
}

double OnpInterpreter::calculate(std::string expression)
{
	validate(expression);
	Stack<std::string> symbols;
	parseExpressionToOnp(expression, symbols);
	result = calculatePostFix(symbols);
	std::cout << result << "\n";
	return result;
}

double OnpInterpreter::operator=(const OnpInterpreter & onp)
{
	return calculate(expr);
}

std::ostream & operator<<(std::ostream & stream, const OnpInterpreter & onp)
{
	stream << onp.result << "\n";
	return stream;
}
