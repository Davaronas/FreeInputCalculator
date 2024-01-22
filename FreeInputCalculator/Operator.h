#pragma once
#include "ExpressionPart.h"
#include <ostream>

enum OperatorType { None, Plus, Minus, Multiply, Divide, Mod, Power};

class Operator : public ExpressionPart
{
private:
	OperatorType opType;
	int priority;
	bool canBeUnary;
	bool isUnary;
	char ConvertOpTypeToChar() const;
	OperatorType ConvertCharToOp(char c) const;

public:
	Operator(char c, ExpressionPart* _prev = nullptr);
	OperatorType GetOperatorType();
	virtual ~Operator();

	int ProcessInput(std::string original, size_t& index) override;
	virtual std::ostream& DisplayForm(std::ostream& os) const override;
	virtual void DisplayType() const override;

	int GetPriority() const;
	bool CanBeUnary() const { return canBeUnary; }
	void SetToUnary();
	bool IsUnary() const { return isUnary; };

};

