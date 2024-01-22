#pragma once
#include "ExpressionPart.h"
#include <string>
#include <ostream>

class Number : public ExpressionPart
{
private:
	double num;
	std::string strNum;

public:
	Number(ExpressionPart* _prev = nullptr);
	Number(double _num, ExpressionPart* _prev = nullptr);
	virtual ~Number();
	void Concatenate(char c);
	void Finish();

	int ProcessInput(std::string original, size_t& index) override;
	virtual std::ostream& DisplayForm(std::ostream& os) const override;
	virtual void DisplayType() const override;

	double GetNumber();


};

