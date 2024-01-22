#include "Calculator.h"
#include <map>
#include <iostream>




bool Calculator::Calculate(ExpressionPart*& exp)
{
	std::cout << std::endl << "=== Calculating Expression ===" << std::endl;
	std::cout << *exp << std::endl << std::endl;
	std::vector<ExpressionPart*>& _expParts = ((Expression*)exp)->GetExpressionParts();
	for (int i{}; i < _expParts.size(); ++i)
	{
		//_expParts[i]->DisplayConnections();

		if (typeid(*(_expParts[i])) == typeid(Expression))
		{
			std::cout << "Start calculation of inner expression at: " << i << std::endl;

			ExpressionPart*& _subExp = _expParts[i];
			ExpressionPart* _prev = _subExp->GetPrev();
			ExpressionPart* _next = _subExp->GetNext();



			//std::cout << *exp << std::endl;
			
			std::cout << *_subExp << std::endl;
			if (!Calculate(_subExp))
			{
				std::cout << "FAILED: Calculation failed due to (most likely) a zero division" << std::endl << std::endl;
				return false;
			}
			std::cout << *exp << std::endl;
			

			if (_prev != nullptr)
			{
				_subExp->SetPreviousPointer(_prev);
				_prev->SetNextPointer(_subExp);
			}

			if (_next != nullptr)
			{
				_subExp->SetNextPointer(_next);
				_next->SetPreviousPointer(_subExp);
			}

			_expParts[i] = _subExp;
			std::cout << "Finished calculating inner expression at: " << i << " Sub Result: "
				<< ((Number*)_subExp)->GetNumber() << std::endl << std::endl;

			
		}
	}


	ExpressionPart* op{ nullptr };
	ExpressionPart* newReturned{ nullptr };
	int opIndex{ -1 };
	std::vector<int> _indexesDeleted = {};
	do {
		op = FindHighestPriorityOperator(exp, opIndex);
		if (opIndex > -1)
		{
			
			if (ExecuteOperation(op, newReturned, _expParts,  opIndex, _indexesDeleted))
			{
				std::cout << std::endl << "Calculating at index " << opIndex << std::endl; 
				for (int j{}; j < _indexesDeleted.size(); ++j)
				{
					_expParts[_indexesDeleted[j]] = nullptr;
					std::cout << "	using number at index " << _indexesDeleted[j] << std::endl;
				}
				_expParts[opIndex] = newReturned;
				_indexesDeleted.clear();
				

				std::cout << *exp << std::endl << std::endl;
			}
			else
			{
				std::cout << "FAILED: Operation execution failed" << std::endl << std::endl;
				return false;
			}
		}

	} while (op != nullptr);




	if (newReturned == nullptr) 
	{
		for (int i{}; i < _expParts.size(); ++i)
		{
			if (typeid(*(_expParts[i])) == typeid(Number))
			{
				newReturned = _expParts[i];
			}
		}
	}

	delete exp;
	exp = nullptr;
	exp = newReturned;
	return true;


	/*
	for (int i{}; i < _expParts.size(); ++i)
	{
		if (_expParts[i] != nullptr)
		{
			delete exp;
			exp =  _expParts[i];
		}
	}
	*/
	//std::cout << "===== Calculating Expression Finished =====" << std::endl;
}



bool Calculator::ExecuteOperation(ExpressionPart*& op, ExpressionPart*& _new,
	std::vector<ExpressionPart*>& _expParts, int opIndex, std::vector<int>& indexesDeleted)
{
	// Set vector pointers to nullptr

	if (op == nullptr)
	{
		return true;
	}

	bool isUnary = ((Operator*)op)->IsUnary();
	OperatorType operationType = ((Operator*)op)->GetOperatorType();


	if (!isUnary)
	{
		// Binary
		ExpressionPart* _prev{ op->GetPrev() };
		ExpressionPart* _next{ op->GetNext() };
		ExpressionPart* _prevPrev{ nullptr };
		ExpressionPart* _nextNext{ nullptr };
	//	ExpressionPart* _prevPrevNext{ nullptr };
	//	ExpressionPart* _nextNextPrev{ nullptr };

		if (_prev != nullptr)
		{
			_prevPrev = _prev->GetPrev();
		}
		else
		{
			std::cout << "ERROR: Binary operation has nullpointer on previous neighbour at: " << opIndex << std::endl;
			return false;
		}

		if (_next != nullptr)
		{
			_nextNext = _next->GetNext();
		}
		else
		{
			std::cout << "ERROR: Binary operation has nullpointer on next neighbour at: " << opIndex << std::endl;
			return false;
		}

		double _res{};
		double a{ ((Number*)_prev)->GetNumber() };
		double b{ ((Number*)_next)->GetNumber() };

		switch (operationType)
		{
		case OperatorType::Plus:
			_res = Add(a, b);
			break;
		case OperatorType::Minus:
			_res = Subtract(a, b);
			break;
		case OperatorType::Multiply:
			_res = Multiply(a, b);
			break;
		case OperatorType::Divide:
			_res = Divide(a, b);
			break;
		case OperatorType::Mod:
			_res = Mod(a, b);
			break;
		case OperatorType::Power:
			_res = Power(a, b);
			break;
		case OperatorType::None:
			_res = nan("1");
			break;
		}


		if (isnan(_res))
		{
			return false;
		}

		for (int i{}; i < _expParts.size(); ++i)
		{
			if (_prev == _expParts[i])
			{
				indexesDeleted.push_back(i);
			//	std::cout << "prev ExpressionPart* to be deleted at index: " << i << std::endl;

				break;
			}
		}

		for (int i{}; i < _expParts.size(); ++i)
		{
			if (_next == _expParts[i])
			{
				indexesDeleted.push_back(i);
			//	std::cout << "next ExpressionPart* to be deleted at index: " << i << std::endl;
				break;
			}
		}


		delete op;
		op = nullptr;
		delete _prev;
		_prev = nullptr;
		delete _next;
		_next = nullptr;



		//indexesDeleted.push_back(opIndex - 1);
		//indexesDeleted.push_back(opIndex + 1);
		// Vannak üresek közte, nem bíztos hogy +1 -1

		_new = new Number{ _res };
		
		
		op = _new;

		if (_prevPrev != nullptr)
		{
		//	std::cout << "_prevPrev not null at " << opIndex << std::endl;
			_prevPrev->SetNextPointer(((Number*)_new));
			_new->SetPreviousPointer(_prevPrev);
			//_prevPrevNext->Set ((Number*)_new);
			//_new->SetPreviousPointer(_prevPrev);

			

		}

		if (_nextNext != nullptr)
		{
		//	std::cout << "_nextNext not null at " << opIndex << std::endl;

			_nextNext->SetPreviousPointer(((Number*)_new));
			_new->SetNextPointer(_nextNext);
			//_nextNextPrev = ((Number*)_new);
		//	_new->SetNextPointer(_nextNext);

		
		}

		return true;

	}
	else
	{
		// Unary

		ExpressionPart* _next{ op->GetNext() };
		ExpressionPart* _nextNext{ nullptr };
		//ExpressionPart* _nextNextPrev{ nullptr };



		if (_next != nullptr)
		{
			_nextNext = _next->GetNext();

		}
		else
		{
			std::cout << "Unary operation has nullpointer on next neighbour" << std::endl;
			return false;
		}

		double _res{};
		double a{ ((Number*)_next)->GetNumber() };

		switch (operationType)
		{
		case OperatorType::Plus:
			_res = nan("2");
			break;
		case OperatorType::Minus:
			_res = Minus(a);
			break;
		case OperatorType::Multiply:
			_res = nan("2");
			break;
		case OperatorType::Divide:
			_res = nan("2");
			break;
		case OperatorType::Mod:
			_res = nan("2");
			break;
		case OperatorType::Power:
			_res = nan("2");
			break;
		case OperatorType::None:
			_res = nan("1");
			break;
		}


		if (isnan(_res))
		{
			return false;
		}

		for (int i{}; i < _expParts.size(); ++i)
		{
			if (_next == _expParts[i])
			{
				indexesDeleted.push_back(i);
				break;
			}
		}


		delete op;
		op = nullptr;
		delete _next;
		_next = nullptr;

		//indexesDeleted.push_back(opIndex + 1);

		_new = new Number{ _res };
		_new->SetNextPointer(_nextNext);
		op = _new;

		if (_nextNext != nullptr)
		{
			_nextNext->SetPreviousPointer(((Number*)_new));
			//_new->SetNextPointer(_nextNext);
		}

		return true;
	}


	// do calculations
	// assign
	//ExpressionPart* _new = new Number{};

	
	// Get prev pointer
	// Get next pointer
	// Get prev->prev pointer
	// Get prev->prev->next pointer
	// Get next->next pointer
	// Get next->next->prev pointer
	// 
	// 
	// if binary operator:
	// Delete prev and next location
	// if unary:
	// only delete right
	// create new pointer from left and right values with the operator of this location
	// delete current location
	// assign this new pointer to this location


	// Erase nulls from vector!!!! Maybe not
}



ExpressionPart* Calculator::FindHighestPriorityOperator(ExpressionPart*& exp, int& opIndex)
{
	opIndex = -1;

	std::vector<ExpressionPart*> _expParts = ((Expression*)exp)->GetExpressionParts();
	std::map<const int, int> operatorIndexes{};
	for (int i{}; i < _expParts.size(); ++i)
	{
		if (_expParts[i] == nullptr) { continue; }

		if (typeid(*(_expParts[i])) == typeid(Operator)) 
		{
			operatorIndexes.insert({ i ,  ((Operator*)(_expParts[i]))->GetPriority() });
		}
	}

	
	size_t highestPriority = 0;
	for (auto i = operatorIndexes.begin(); i != operatorIndexes.end(); ++i)
	{
		if (i->second > highestPriority)
		{
			highestPriority = i->second;
		}
	}

	for (auto i = operatorIndexes.begin(); i != operatorIndexes.end(); ++i)
	{
		if (i->second == (int)highestPriority)
		{
			opIndex = i->first;
			return _expParts[i->first];
		}
	}

	// no operator found, find a number and set
	
	return nullptr;
}




double Calculator::Minus(double a)
{
	return -a;
}

double Calculator::Power(double a, double b)
{
	return pow(a,b);
}

double Calculator::Multiply(double a, double b)
{
	return a * b;
}

double Calculator::Divide(double a, double b)
{
	if (b == 0)
	{
		std::cout << "FAILED: Zero division" << std::endl;
		return nan("0");
	}
	else
	{
		return a / b;
	}
	
}

double Calculator::Mod(double a, double b)
{
	return fmod(a,b);
}

double Calculator::Add(double a, double b)
{
	return a + b;
}

double Calculator::Subtract(double a, double b)
{
	return a - b;
}
