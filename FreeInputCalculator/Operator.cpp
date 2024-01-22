#include "Operator.h"
#include <string>
#include <iostream>

char Operator::ConvertOpTypeToChar() const
{
    switch (opType)
    {
    case OperatorType::Plus:
        return '+';
        break;
    case OperatorType::Minus:
        return '-';
        break;
    case OperatorType::Multiply:
        return '*';
        break;
    case OperatorType::Divide:
        return '/';
        break;
    case OperatorType::Mod:
        return '%';
        break;
    case OperatorType::Power:
        return '^';
        break;
    case OperatorType::None:
        return '?';
        break;
    }

    return '\0';
}

OperatorType Operator::ConvertCharToOp(char c) const
{
    switch (c)
    {
    case '+':
        return OperatorType::Plus;
        break;
    case '-':
        return OperatorType::Minus;
        break;
    case '*':
        return OperatorType::Multiply;
        break;
    case '/':
        return OperatorType::Divide;
        break;
    case '%':
        return OperatorType::Mod;
        break;
    case '^':
        return OperatorType::Power;
        break;
    }
}

Operator::Operator(char c, ExpressionPart* _prev) :
    opType{ OperatorType::None }, isUnary{ false }, canBeUnary{ false }, ExpressionPart::ExpressionPart(_prev)
{
    opType = ConvertCharToOp(c);

    if (opType == OperatorType::Plus || opType == OperatorType::Minus)
    {
        priority = 1;

        if (opType == OperatorType::Minus)
        {
            canBeUnary = true;
        }
    }
    else if (opType == OperatorType::Multiply || opType == OperatorType::Divide || opType == OperatorType::Mod)
    {
        priority = 2;
    }
    else if (opType == OperatorType::Power)
    {
        priority = 3;
    }

    // Unary Operator state is checked later, will have the highest priority
}

OperatorType Operator::GetOperatorType()
{
    return opType;
}

Operator::~Operator()
{
}

int Operator::ProcessInput(std::string original, size_t& index)
{
    return 2;
}

std::ostream& Operator::DisplayForm(std::ostream& os) const
{
    os << ConvertOpTypeToChar();
    return os;
}

void Operator::DisplayType() const
{
    if (IsUnary())
    {
        std::cout << "Unary";
    }
    std::cout << "Operator ";
}

int Operator::GetPriority() const
{
    return priority;
}

void Operator::SetToUnary()
{
    // Unary operators have highest priority
    isUnary = true;
    priority = 4;
}
