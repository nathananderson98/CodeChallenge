#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "RomanNumeral.h"

/*
		Coded in 3:41:15 for a coding challenge for a position at BYU OIT 
		Roman Numeral and Number Converter, works with input files if provided, otherwise on the console
		I did my best to comment clearly through the code so its easy to follow, enjoy.
*/


void takeOffZero(int &originalNum, int place, int quantity) // created to clarify what the code is doing
{
	originalNum = originalNum - place * quantity;
}

std::string convertNumber(std::string number)  // brute force approach to convert number to roman numerals
{
	std::stringstream ss;
	int num = std::stoi(number);
	int thousands = num / 1000;
	takeOffZero(num, 1000, thousands);
	int hundreds = num / 100;
	takeOffZero(num, 100, hundreds);
	int tens = num / 10;
	takeOffZero(num, 10, tens);
	int ones = num % 10;
	if (thousands > 0)
		for (int i = 0; i < thousands; i++)
			ss << 'M';

	if (hundreds > 0)
	{
		if (hundreds == 9)
		{
			ss << "CM";
			hundreds = 0;
		}
		if (hundreds >= 5)
		{
			ss << 'D';
			hundreds -= 5;
		}
		else if (hundreds == 4)
		{
			ss << "CD";
			hundreds = 0;
		}
		for (int i = 0; i < hundreds; i++)
			ss << 'C';
	}
	if (tens > 0)
	{
		if (tens == 9)
		{
			ss << "XC";
			tens = 0;
		}
		if (tens >= 5)
		{
			ss << 'L';
			tens -= 5;
		}
		else if (tens == 4)
		{
			ss << "XL";
			tens = 0;
		}
		for (int i = 0; i < tens; i++)
			ss << 'X';
	}
	if (ones > 0)
	{
		if (ones == 9)
		{
			ss << "IX";
			ones = 0;
		}
		if (ones >= 5)
		{
			ss << 'V';
			ones -= 5;
		}
		else if (ones == 4)
		{
			ss << "IV";
			ones = 0;
		}
		for (int i = 0; i < ones; i++)
			ss << 'I';
	}
	return ss.str();
}

bool const isNumber(std::string numStr)
{
	bool isNum = true;
	for (int i = 0; i < numStr.size(); i++)
	{
		if (!std::isdigit(numStr[i])) // if every character in the string is a number, isNum will stay true
			isNum = false;
	}
	return isNum;
}

bool const isNumeral(std::string numeralStr)
{
	bool isRom = true;
	std::string numerals = "IVXLCDM";
	for (int i = 0; i < numeralStr.size(); i++)
	{
		char currLetter = numeralStr[i];
		if (numerals.find(currLetter) == std::string::npos) // if every character is found in the numerals string, isRom will stay true
			isRom = false;
	}
	return isRom;
}

std::string determineInput(std::string line)
{
	if (isNumber(line)) // check to see if input is a number
	{
		return convertNumber(line);
	}
	else if (isNumeral(line)) // check to see if input is a roman numeral
	{
		RomanNumeral numeral(line);
		return numeral.convertNumeral(); // creates a roman numeral object and runs the convert member function
	}
	else
	{
		return line + " Invalid Input";
	}
}

void parseFile(std::ifstream& in, std::ofstream& out) // works through the input provided line by line
{
	std::string line;
	while (getline(in, line))
	{
		try
		{
			if (line.size() == 0)
				throw "Input Empty";
			out << determineInput(line) << std::endl; // outputs the converted value to the out file
		}
		catch (std::string e)
		{
			out << e << std::endl;
		}
	}
}

void verifyIntput(int argc, char** argv, std::ifstream& in, std::ofstream& out)
{
	if (argc < 3)
	{
		std::cerr << "Please provide name of input and output files";
	}
	std::cout << "Input file: " << argv[1] << std::endl;
	if (!in)
	{
		std::cerr << "Unable to open " << argv[1] << " for input";
	}
	std::cout << "Output file: " << argv[2] << std::endl;
	if (!out)
	{
		in.close();
		std::cerr << "Unable to open " << argv[2] << " for output";
	}
}

void runConsoleCode()
{
	std::string input;
	std::cout << "--Roman Numeral & Number Converter--\n\nEnter \'quit\' to exit application." << std::endl << "  Enter a Roman Numeral or a Number: ";
	std::cin >> input;
	while (input != "quit")
	{
		if (isNumber(input))  // check to see if input is a number
			std::cout << convertNumber(input);
		else if (isNumeral(input)) // check to see if input is a roman numeral
		{
			RomanNumeral numeral(input);
			std::cout << numeral.convertNumeral();
		}
		else
		{
			std::cout << input << " Invalid Input";
		}
		std::cout << std::endl << "  Enter a Roman Numeral or a Number: ";
		std::cin >> input;
	}
}

int main(int argc, char** argv)
{
	if (argc == 3)  //  checks if inputs are provided for main
	{
		std::ifstream in(argv[1]);
		std::ofstream out(argv[2]);
		verifyIntput(argc, argv, in, out);
		parseFile(in, out);
	}
	else
		runConsoleCode();  // otherwise runs it in console
	return 0;
}