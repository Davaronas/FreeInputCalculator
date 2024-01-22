#pragma once
#include "ExpressionPart.h"
#include "Number.h"
#include "Operator.h"
#include <vector>
#include <string>
#include <ostream>



class Expression : public ExpressionPart
{
private:
	std::vector<ExpressionPart*> expressionParts;
	bool valid;
	double result;
	std::string originalInput;


	ExpressionPart* OpenExpressionPart(std::string original, size_t& i);

	int ProcessInput(std::string original, size_t& index) override;
	

public:
	Expression(std::string _input, ExpressionPart* _prev = nullptr);
	virtual ~Expression();
	std::vector<ExpressionPart*>& GetExpressionParts();
	bool EstablishConnections();
	bool CheckConnectionValidity(size_t& size);
	bool IsValidConnection(ExpressionPart*& expressionPart);

	

	virtual std::ostream& DisplayForm(std::ostream& os) const override;
	virtual void DisplayType() const override;

	bool IsValid() { return valid; };
	double GetResult();

};

