#pragma once
#include "Expression.h"


class Calculator
{
public:
	
	bool Calculate(ExpressionPart*& exp);

	bool ExecuteOperation(ExpressionPart*& op, ExpressionPart*& _new, std::vector<ExpressionPart*>& _expParts,
		int opIndex, std::vector<int>& indexesDeleted);
	ExpressionPart* FindHighestPriorityOperator(ExpressionPart*& exp, int& opIndex);


	double Minus(double a);

	double Power(double a, double b);

	double Multiply(double a, double b);
	double Divide(double a, double b);
	double Mod(double a, double b);

	double Add(double a, double b);
	double Subtract(double a, double b);

	// double Factorial(int a);


	// zero division
};

