#include "Number.h"
#include "InputReader.h"
#include <iostream>

Number::Number(ExpressionPart* _prev) : num{0}, strNum{}, ExpressionPart::ExpressionPart(_prev)
{

}

Number::Number(double _num, ExpressionPart* _prev) : num{_num}, strNum{}, ExpressionPart::ExpressionPart(_prev)
{

}

Number::~Number()
{

}

void Number::Concatenate(char c)
{
    strNum.push_back(c);
}

void Number::Finish()
{
    if (!strNum.empty())
    {
        num = stoi(strNum);
    }
}

int Number::ProcessInput(std::string original, size_t& index)
{
    if (index >= original.length()) { Finish(); return 0; }

    if (IsDigit(original[index]))
    {
        Concatenate(original[index]);
        ++index;
        return 1;
    }
    else
    {
        Finish();
        return 2;
    }
}

std::ostream& Number::DisplayForm(std::ostream& os) const
{
    os << " " << num << " ";
    return os;
}

void Number::DisplayType() const
{
    std::cout << "Number ";
}

double Number::GetNumber()
{
    return num;
}
