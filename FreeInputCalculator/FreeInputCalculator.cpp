

#include <iostream>
#include <windows.h>
#include <iomanip>
#include <string>
#include "InputReader.h"
#include "Calculator.h"
#include "ExpressionPart.h"

using namespace std;


void TestInput(InputReader _inputReader, Calculator _calculator, string _test);

int main()
{
    static CONSOLE_FONT_INFOEX  fontex;
    fontex.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);
    GetCurrentConsoleFontEx(hOut, 0, &fontex);
    fontex.FontWeight = 100;
    fontex.dwFontSize.X = 20;
    fontex.dwFontSize.Y = 20;
    SetCurrentConsoleFontEx(hOut, NULL, &fontex);

    std::cout << std::setprecision(10);

    InputReader IR;
    Calculator calculator{};

    vector<string> testInputs{
        // 3 + 245 - (200 - (-2) + 300 - (30 * 2 + (30 - 20 + (400 - (-5 / 0))))) ",
              //  "3 + )",
              //  " 3 + 4 + (5 +* 2)",
             //   " 2 + (2 + (-2))",
             //   "2 + 300 - (200 * 3 + 4) -3 + 2 * 3 / 2"
               // "3 + (2 -3) - 2",
             //   "3 + 2 * 30", // 63
             //   "20 - (5 + 2)", // 13
             //   "3 + 200 - (5 * 2 - 2 * (3 - 1)) + 3" // 200

    };

    for (int i{}; i < testInputs.size(); ++i)
    {
        TestInput(IR, calculator, testInputs[i]);
    }


    double _res{};
    string input{};

    ExpressionPart* mainExpression{ nullptr };

    
    std::cout << "=========START OF PROCEDURE==========" << endl << endl;
    std::cout << "Type exit to quit" << endl << endl;
    std::getline(cin, input);
    std::system("cls");


    while (input != "Exit" && input != "exit")
    {
        std::cout << "=========START OF PROCEDURE==========" << endl << endl;
        std::cout << "Type exit to quit" << endl << endl;

        std::cout << input << endl << endl;
        mainExpression = IR.Evaluate(input);
        std::cout << endl;

        if (mainExpression != nullptr)
        {
            if (calculator.Calculate(mainExpression))
            {
                if (mainExpression != nullptr)
                {
                    _res = ((Number*)mainExpression)->GetNumber();
                    delete mainExpression;
                    mainExpression = nullptr;
                    std::cout << endl << "Result: " << _res << endl << endl;
                    std::cout << input << " = " << _res << endl << endl;
                    std::cout << "=========END OF PROCEDURE==========" << endl << endl;
                }
               
            }
        }

        delete mainExpression;
        mainExpression = nullptr;
        std::getline(cin, input);
        
        std::system("cls");
        
    }
    

}


void TestInput(InputReader _inputReader, Calculator _calculator, string _test)
{
    std::cout << "=========START OF PROCEDURE==========" << endl << endl;
    std::cout << _test << endl << endl;
    ExpressionPart* mainExpression{nullptr};
    mainExpression = _inputReader.Evaluate(_test);
   
    double _res{};

    if (mainExpression != nullptr)
    {
       // cout << *mainExpression << endl << endl;
        if (_calculator.Calculate(mainExpression))
        {
            if (mainExpression != nullptr)
            {
                _res = ((Number*)mainExpression)->GetNumber();
                std::cout << endl << "Result: " << _res << endl << endl;
                std::cout << _test << " = " << _res << endl << endl;
            }

        }
    }
    delete mainExpression;
    mainExpression = nullptr;
    std::cout  << "=========END OF PROCEDURE==========" << endl;
    std::cout << endl << endl;

}
