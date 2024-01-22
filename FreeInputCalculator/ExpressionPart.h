#pragma once
#include <string>


class ExpressionPart
{
protected:
	ExpressionPart* prev;
	ExpressionPart* next;

public:
	// return 0 - Finished, reached last character of input
	// return 1 - Input succesfully processed, keep reading input
	// return 2 - Input cannot be processed by this Expression part, keep reading input
	// return -1 - Invalid syntax or something else went wrong
	virtual int ProcessInput(std::string original, size_t& index) = 0;
	virtual std::ostream& DisplayForm(std::ostream& os) const = 0;
	virtual void DisplayType() const = 0;
	void DisplayConnections() const;
	void SetNextPointer(ExpressionPart* _next);
	void SetPreviousPointer(ExpressionPart* _prev);
	ExpressionPart(ExpressionPart* _prev = nullptr);
	virtual ~ExpressionPart();
	ExpressionPart*& GetPrev();
	ExpressionPart*& GetNext();

	friend std::ostream& operator<<(std::ostream& os, const ExpressionPart& rhs);

	bool operator==(const ExpressionPart*& rhs);

};

