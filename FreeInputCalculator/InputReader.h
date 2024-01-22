#pragma once
#include <string>
#include "Expression.h"


bool IsDigit(char c);
bool IsOperator(char c);
bool IsStartingBracket(char c);
bool IsEndingBracket(char c);
static constexpr const char* numberDictionary = "0123456789"; // ^ sqrt
static constexpr const char* operatorDictionary = "+-*/%^";
static constexpr const char startingBracket = '(';
static constexpr const char endingBracket = ')';
static constexpr size_t operatorDictionaryLength{6};  // Keep checking if you add new operators

class InputReader
{
private:
	static constexpr const char* dictionary = "0123456789 +-*/%^()"; // ^ sqrt
	size_t dictionarySize;

public:
	InputReader();
	~InputReader();

	Expression* Evaluate(const std::string& _input);
	
	bool CharactersValid(const std::string& _input);

};



// [5 + 6 - (2 * 2) / 5]
// Create part: Get numbers (or bracket start) until operator found : 5 
// Create part: Get operator (or bracket end) : +
// Create part: Get numbers (or bracket start) until operator found : 6
// Create part: Get operator (or bracket end) : -
// Create part: Get numbers (or bracket start) until operator found : Found bracket start (
//  Create part: Get number from bracket -> 4
//		Create part: Get numbers (or bracket start) until operator found : 2
//		Create part: Get operator (or bracket end) : *
//		Create part: Get numbers (or bracket start) until operator found : 2
//		Create part: Get operator (or bracket end) : Found bracket end )
//		EXPRESSION END : START CALCULATION
//		Get highest importance operator: get highest that is located the closest to the start (closest to left) : *
//		Set left side part to new :
//			Get left and right number and calculate the operation : *2 = 2 * 2 -> 4
//			delete operator and right side from parts : delete * location, delete 2 (rhs) location
//  		Get highest importance operator: get highest that is located the closest to the start (closest to left) : \0
//			NO MORE OPERATORS : RETURN THE ONLY NUMBER LEFT
// [5 + 6 - 4 / 5]
// Create part: Get operator (or bracket end) : /
// Create part: Get numbers (or bracket start) until operator found : 5 
// Create part: Get operator (or bracket end) : \0
// FOUND END OF STRING
// EXPRESSION END : START CALCULATION
// Get highest importance operator: get highest that is located the closest to the start (closest to left) : /
// Set left side part to new :
//		Get left and right number and calculate the operation : *4 = 4 / 5 -> 0.8
//		delete operator and right side from parts : delete / location, delete 5 (rhs) location
// [5 + 6 - 0.8]
// Get highest importance operator: get highest that is located the closest to the start (closest to left) : +
// Set left side part to new :
//		Get left and right number and calculate the operation : *5 = 5 + 6 -> 11
//		delete operator and right side from parts : delete + location, delete 6 (rhs) location
// [11 - 0.8]
// Get highest importance operator: get highest that is located the closest to the start (closest to left) : -
// Set left side part to new :
//		Get left and right number and calculate the operation : *11 = 11 - 0.8 -> 10.2
//		delete operator and right side from parts : delete - location, delete 0.8 (rhs) location
// [11]
// Get highest importance operator: get highest that is located the closest to the start (closest to left) : \0
// NO MORE OPERATORS : RETURN THE ONLY NUMBER LEFT



