#ifndef ROMANNUMERAL_H
#define ROMANNUMERAL_H
#include <stack>
#include <string>
#include <sstream>


class RomanNumeral
{
private:
	std::string numeral;
public:
	RomanNumeral(std::string input) { numeral = input; };
	std::string convertNumeral();
	int numeralToValue(char rn);
	char checkTensValidity(std::string rn);
};

std::string RomanNumeral::convertNumeral()
{
	std::stack<char> romanStack;
	std::string tempNumeral = numeral;
	std::string numeralOrder = "IVXLCDM";
	int finalNumber = 0;
	char tenCheck = checkTensValidity(tempNumeral);
	if (tenCheck != 'a')
	{
		std::stringstream ss;
		ss << "~" << tenCheck << tenCheck << tenCheck << tenCheck << "~" << " : Invalid Numeral, Use '" << numeralOrder[numeralOrder.find(tenCheck) + 1] << "' instead.";
		return ss.str();
	}

 	while (tempNumeral.size() != 0)
	{
		char currNum = tempNumeral[0];
		if (romanStack.size() == 0)
		{
			romanStack.push(currNum);
		}
		else
		{
			char topStack = romanStack.top();
			int stackTopOrd = numeralOrder.find(topStack);
			int tempFrontOrd = numeralOrder.find(currNum);
			if (stackTopOrd > tempFrontOrd)
			{
				finalNumber += numeralToValue(topStack);
				romanStack.pop();
				romanStack.push(currNum);
			}
			else if (stackTopOrd == tempFrontOrd)
			{
				if (stackTopOrd == 1 || stackTopOrd == 3 || stackTopOrd == 5) // Can't have more than one 5, 50 or 500 numeral, checks for this condition
				{
					std::stringstream ss;
					ss << "~" << topStack << currNum << "~" << " : Invalid Numeral, Use '" << numeralOrder[tempFrontOrd + 1] << "' instead.";
					return ss.str();
				}
				romanStack.push(currNum);
			}
			else
			{
				if (stackTopOrd + 2 < tempFrontOrd) // checks if the numerals are in order, no I's subtracting M's for example
				{
					std::stringstream ss;
					ss << "~" << topStack << currNum << "~" << " : Invalid Numeral Mismatch, Use '" << numeralOrder[tempFrontOrd - 2] << currNum << "' instead";
					return ss.str();
				}
				romanStack.pop();
				if (romanStack.size() > 0)									 //  <- checks to see if more than one lesser numeral is modifying current numeral
					if (numeralOrder.find(romanStack.top()) < tempFrontOrd)  //  <--
					{
						std::stringstream ss;
						ss << "~" << topStack << romanStack.top() << currNum << "~" << " : Invalid Numeral, Only one subtracting numeral allowed.";
						return ss.str();
					}
				finalNumber -= numeralToValue(topStack);
				romanStack.push(currNum);
			}
		}
		tempNumeral.erase(0, 1);
	}
	int size = romanStack.size();
	for (int i = 0; i < size; i++)  // gets the rest of the stack numerals converted into nums and adds them to the value
	{
		finalNumber += numeralToValue(romanStack.top());
		romanStack.pop();
	}
	return std::to_string(finalNumber);
}

int RomanNumeral::numeralToValue(char romanNumeral)  // converts the numeral into an int value
{
	if (romanNumeral == 'M')
		return 1000;
	else if (romanNumeral == 'D')
		return 500;
	else if (romanNumeral == 'C')
		return 100;
	else if (romanNumeral == 'L')
		return 50;
	else if (romanNumeral == 'X')
		return 10;
	else if (romanNumeral == 'V')
		return 5;
	else if (romanNumeral == 'I')
		return 1;
	else
		return 0;
}

char RomanNumeral::checkTensValidity(std::string numeral)  // checks to see if the numeral uses an unnecessary amount of ten units numerals (four or more).
{
	if (numeral.size() < 4)
		return 'a'; // clears
	else
	{
		for (int i = 0; i < numeral.size() - 3; i++)
		{
			char zero = numeral[i];
			char one = numeral[i + 1];
			char two = numeral[i + 2];
			char three = numeral[i + 3];
			if (zero == one && one == two && two == three)
				return zero;
		}
	}
	return 'a'; // clears
}

#endif

