#include "Expression.h"
#include "InputReader.h"
#include <iostream>


Expression::Expression(std::string _input, ExpressionPart* _prev) 
    : valid{ true }, originalInput{ _input }, result{ nan("3") }, ExpressionPart(_prev)
{
    expressionParts = {};
    size_t index{ 0 };
    int _state = ProcessInput(_input, index);

    if (_state == -1)
    {
        valid = false;

        std::cout << "FAILED: Invalid syntax in input or invalid neighbour in inner expression" << std::endl << std::endl;
        std::cout << _input << std::endl;


        char* arrow1 = new char[_input.length() + 1];

        for (size_t a1{}; a1 < _input.length(); ++a1)
        {
            if (a1 == index)
            {
                *(arrow1 + a1) = '^';
            }
            else
            {
                *(arrow1 + a1) = ' ';
            }
            std::cout << *(arrow1 + a1);
        }
        std::cout << std::endl;

        delete[] arrow1;
    }
    else
    {
        valid = EstablishConnections();
    }

}



Expression::~Expression()
{

}





ExpressionPart* Expression::OpenExpressionPart(std::string original, size_t& index)
{
    if (index >= original.length()) { return nullptr; };

    ExpressionPart* _newExpressionPart{ nullptr };

    if (IsDigit(original[index]))
    {
        _newExpressionPart = new Number{};
        return _newExpressionPart;
    }

    if (IsOperator(original[index]))
    {
        _newExpressionPart = new Operator{ original[index++] };
        return _newExpressionPart;
    }

    if (IsEndingBracket(original[index]))
    {
        std::cout << "ERROR: Ending bracket found for creating expression, probably wrong input" << std::endl;
    }

    if (IsStartingBracket(original[index]))
    {
        size_t brackets{ 1 };
        size_t newIndex = index + 1;
        size_t newIndexStart = newIndex;
        size_t bracketsFound{ 0 };
        if (newIndex >= original.length())
        {
            _newExpressionPart = nullptr;
            return _newExpressionPart;
        }

        for (newIndex; newIndex < original.length(); ++newIndex)
        {
            if (IsStartingBracket(original[newIndex]))
            {
                ++brackets;
                ++bracketsFound;
            }
            else if (IsEndingBracket(original[newIndex]))
            {


                --brackets;
                if (brackets <= 0)
                {
                    if (newIndex == newIndexStart) // Empty bracket
                    {
                        _newExpressionPart = nullptr;
                        return _newExpressionPart;
                    }

                    index = newIndex + 1; // bracketsFound;
                    _newExpressionPart = new Expression{ original.substr(newIndexStart, newIndex - newIndexStart) };
                    if (!((Expression*)_newExpressionPart)->IsValid())
                    {
                        delete _newExpressionPart;
                        _newExpressionPart = nullptr;
                    }
                    return _newExpressionPart;
                }
            }
        }
    }

    std::cout << "ERROR: At index " << index << " the character cannot start any expression: " << original[index] << std::endl;
    return _newExpressionPart;
}

int Expression::ProcessInput(std::string original, size_t& index)
{
    // no 2 here, read cannot fail: 
    // either open new expression to read
    // or continue with already opened one


    ExpressionPart* currentExpressionPart{ nullptr };

    while (index < original.length())
    {
        expressionStartOver:
        currentExpressionPart = OpenExpressionPart(original, index);
        if (currentExpressionPart == nullptr)
        {
            // OpenExpressionPart Failed
            std::cout << "ERROR: Trying to open expression with an overflown index, or failed expression open, stopping..." << std::endl << std::endl;
            return -1;
        }
        
        if(typeid(*currentExpressionPart) == typeid(Expression))
        {
            // after opening the expression, we need to close it, after we checked if it failed or not
            expressionParts.push_back(currentExpressionPart);
            currentExpressionPart = nullptr;

            if (index >= original.length())
            {
                break;
            }
            else
            {
                goto expressionStartOver;
            }
        }

        int _return{ 99 };
        while (_return != 2)
        {
            _return = currentExpressionPart->ProcessInput(original, index);
            if (_return == 0)
            {
                expressionParts.push_back(currentExpressionPart);
                currentExpressionPart = nullptr;
                return 0;
            }

            if (_return == -1)
            {
                std::cout << "ERROR: processing input failed at: " << index << " as " << *currentExpressionPart << std::endl;
                currentExpressionPart = nullptr;
                return -1;
            }
        }
        // 2 means couldn't read with current part, push back current and create new


        // Push back
        expressionParts.push_back(currentExpressionPart);
        currentExpressionPart = nullptr;
    }

    if (index >= original.length()) { return 0; };

    return 1;
}

std::ostream& Expression::DisplayForm(std::ostream& os) const
{
    os << "[";
    for (size_t i{}; i < expressionParts.size(); ++i)
    {
        if (expressionParts[i] != nullptr)
        {
            os << *(expressionParts[i]);
        }
        else
        {
            os << " _ ";
        }
    }
    os << "] ";
    return os;
}

void Expression::DisplayType() const
{
    std::cout << "Expression[";
    for (size_t i{}; i < expressionParts.size(); ++i)
    {
        expressionParts[i]->DisplayType();
    }
    std::cout << "] ";
}

double Expression::GetResult()
{
    return result;
}




std::vector<ExpressionPart*>& Expression::GetExpressionParts()
{
    return expressionParts;
}

bool Expression::EstablishConnections()
{
    std::cout << "===== Establishing Connections for expression =====" << std::endl;
    std::cout << *this << std::endl << std::endl;
    size_t size = expressionParts.size();
    for (int i{}; i < size; ++i)
    {
        if (i > 0)
        {
            expressionParts[i]->SetPreviousPointer(expressionParts[i - 1]);
        }

        if (i < size - 1)
        {
            expressionParts[i]->SetNextPointer(expressionParts[i + 1]);
        }

        expressionParts[i]->DisplayConnections();
    }
    std::cout << "===== Established Connections for expression =====" << std::endl << std::endl;

    return CheckConnectionValidity(size);
}

bool Expression::CheckConnectionValidity(size_t& size)
{
    for (int i{}; i < size; ++i)
    {
        if (!IsValidConnection(expressionParts[i]))
        {
            std::cout << std::endl << "FAILED: Invalid neighbour at the " << (i + 1) << ". element" << std::endl
                << originalInput << std::endl << std::endl;
            DisplayType();
            std::cout << std::endl << std::endl;
            return false;
        }
    }

    return true;
}

bool Expression::IsValidConnection(ExpressionPart*& expressionPart)
{
    ExpressionPart*& _prev{ expressionPart->GetPrev() };
    ExpressionPart*& _next{ expressionPart->GetNext() };

    // NUMBER OR EXPRESSION
    if (typeid(*expressionPart) == typeid(Expression) || typeid(*expressionPart) == typeid(Number)) 
    {
        if (_prev != nullptr)
        {
            // Okay so far

            if (typeid(*_prev) != typeid(Operator))
            {
                // That's a problem, expression must be followed by an operator
                return false;
            }
        }

        if (_next != nullptr)
        {
            // Okay so far

            if (typeid(*_next) != typeid(Operator))
            {
                // That's a problem, expression must be followed by an operator
                return false;
            }
        }
    }
    else if (typeid(*expressionPart) == typeid(Operator)) // OPERATOR
    {

        if (_prev == nullptr)
        {
            // Operator previous cannot be null, this is a problem, unless this is a unary operator
            if (((Operator*)(expressionPart))->CanBeUnary())
            {
                ((Operator*)(expressionPart))->SetToUnary();
            }
            else
            {
                return false;
            }

        }
        else if(typeid(*_prev) == typeid(Expression) || typeid(*_prev) == typeid(Number))
        {
            // This is the normal behaviour
        }
        else if (typeid(*_prev) == typeid(Operator))
        {
            // We are searching from left, so the neighbouring operator will regard it as invalid neighbour anyway

            /*
            //Operator previous cannot be an operator, this is a problem, unless this is a unary operator
            if (((Operator*)(expressionPart))->CanBeUnary())
            {
                ((Operator*)(expressionPart))->SetToUnary();
            }
            else
            {
                return false;
            }
            */
        }
       
        if (_next == nullptr)
        {
            // Operator next cannot be null, this is a problem
            return false;
        }
        else if (typeid(*_next) == typeid(Expression) || typeid(*_next) == typeid(Number))
        {
            // This is the normal behaviour
        }
        else if (typeid(*_next) == typeid(Operator))
        {
            //Operator next cannot be an operator, this is a problem
            return false;
        }
    }

    return true;
}



