#include "InputReader.h"
#include "Expression.h"
#include <iostream>

InputReader::InputReader()
{
	dictionarySize = strlen(dictionary);
}

InputReader::~InputReader()
{

}

Expression* InputReader::Evaluate(const std::string& _input)
{
	if (!CharactersValid(_input))
	{
		return nullptr;
	}
	
	std::string _inputStripped{};

	for (size_t i{}; i < _input.length(); ++i)
	{
		if (_input[i] != ' ')
		{
			_inputStripped.push_back(_input[i]);
		}
	}

	// strip input of spaces !!!!
	Expression* mainExpression = new Expression { _inputStripped };

	if (mainExpression->IsValid())
	{
		std::cout << *mainExpression << std::endl;
		std::cout << std::endl << "Format: " << std::endl;
		mainExpression->DisplayType();
		std::cout << std::endl;
	}
	else
	{
		return nullptr;
	}

	std::cout << std::endl << "=============== EVALUATION SUCCESSFULL ===============" << std::endl << std::endl;

	Expression* res{ nullptr };
	res = mainExpression;
	return res;
}




bool InputReader::CharactersValid(const std::string& _input)
{
	bool _foundCharacter = false;
	for (size_t i{}; i < _input.length(); ++i)
	{
		_foundCharacter = false;
		for (size_t j{}; j < dictionarySize; ++j)
		{
			if (_input[i] == dictionary[j])
			{
				_foundCharacter = true;
				break;
			}
		}

		if (!_foundCharacter)
		{
			std::cout  << "FAILED: Invalid character in input" << std::endl << std::endl;
			std::cout << _input << std::endl;


			char* arrow1 = new char[_input.length() + 1];

			for (size_t a1{}; a1 < _input.length(); ++a1)
			{
				if (a1 == i)
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

			delete [] arrow1;
			

			return false;
		}
	}

	return true;
}

bool IsDigit(char c)
{
	for (size_t i{}; i < 10; ++i) // 10 - digits
	{
		if (c == numberDictionary[i])
		{
			return true;
		}
	}

	return false;
}

bool IsOperator(char c)
{
	for (size_t i{}; i < operatorDictionaryLength; ++i) // 10 - digits
	{
		if (c == operatorDictionary[i])
		{
			return true;
		}
	}

	return false;
}

bool IsStartingBracket(char c)
{
	return c == startingBracket;
}

bool IsEndingBracket(char c)
{
	return c == endingBracket;
}
