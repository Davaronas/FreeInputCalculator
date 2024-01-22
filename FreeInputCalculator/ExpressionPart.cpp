#include "ExpressionPart.h"
#include <iostream>

std::ostream& operator<<(std::ostream& os, const ExpressionPart& rhs)
{
	rhs.DisplayForm(os);
	return os;
}

void ExpressionPart::DisplayConnections() const
{
	if (prev != nullptr)
	{
		std::cout << *prev;
	}

	std::cout << " <--| " << *this << " |--> ";

	if (next != nullptr)
	{
		std::cout << *next;
	}
	std::cout << std::endl;
}

void ExpressionPart::SetNextPointer(ExpressionPart* _next)
{
	next = _next;
}

void ExpressionPart::SetPreviousPointer(ExpressionPart* _prev)
{
	prev = _prev;
}

ExpressionPart::ExpressionPart( ExpressionPart* _prev) : prev{ _prev }, next{ nullptr }
{

}

ExpressionPart::~ExpressionPart()
{
}

ExpressionPart*& ExpressionPart::GetPrev()
{
	return prev;
}

ExpressionPart*& ExpressionPart::GetNext()
{
	return next;
}



bool ExpressionPart::operator==(const ExpressionPart*& rhs)
{
	if (rhs == nullptr) {
		return false;
	}

	return this == rhs;

	
}
