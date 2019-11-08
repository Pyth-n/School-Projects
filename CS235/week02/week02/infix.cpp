/***********************************************************************
 * Module:
 *    Week 02, Stack
 *    Brother Helfrich, CS 235
 * Author:
 *    David Donovan, David Perez, Jeffry Simpson
 * Summary:
 *    This program will implement the testInfixToPostfix()
 *    and testInfixToAssembly() functions
 ************************************************************************/

#include <iostream>	// for ISTREAM and COUT
#include <string>      	// for STRING
#include <cassert>	// for ASSERT
#include <locale>	// Used for isalnum()
#include "infix.h"	// Used as prototypes
#include <sstream>	// Used to split a string
#include <vector>	// Used for split strings
#include "stack.h"	// for STACK

using namespace std;

/*****************************************************
 * CONVERT INFIX TO POSTFIX
 * Convert infix equation "5 + 2" into postifx "5 2 +"
 * Referenced from the book with modified integration
 *****************************************************/
string convertInfixToPostfix(const string & infix)
{
	char token,		// Character in expression
		  topToken;	// Token on top of Stack
        string postfix; // Postfix expression
	Stack <char> opStack; // Stack for operators

	const string BLANK = " "; // Give spaces
   
	bool onePeriod = true;

	// Let's iterate through the string
	for (int i = 0; i < infix.length(); i++)
	{
		token = infix[i];
		switch (token)
		{
		case ' ': break; // Skip spaces
		case '(':
			// Push left parenthesis
			opStack.push(token);
			break;
		case ')':
			// Pop the left parenthesis
			for (;;)
			{
				topToken = opStack.top();
				opStack.pop();
				if (topToken == '(') break;
				postfix.append(BLANK + topToken);
			}
			break;
		case '^':
			for (;;)
			{
				// If Stack empty, push to Stack
				if (opStack.empty())
				{
					opStack.push(token);
					break;
				}
				// If Stack not empty, push when top is lesser priority
				if (!opStack.empty() && priority(opStack.top()) < 3)
				{
					opStack.push(token);
					break;
				}
			}
			break;
		case '+':
		case '-':
		case '*':
		case '/':
			// Add other operators to Stack
			for (;;)
			{
				if (opStack.empty() || opStack.top() == '(' || 
					(token == '*' || token == '/' || token == '%') && 
					(opStack.top() == '+' || opStack.top() == '-'))
				{
					opStack.push(token);
					break;
				}
				else
				{
					topToken = opStack.top();
					opStack.pop();
					postfix.append(BLANK + topToken);
				}
			}
			break;
		default: 
			// Avoids spaces between periods, otherwise there is spaces
			if (token == '.' && onePeriod) 
			{
				postfix.append(1, token);
				onePeriod = false;
			}
			else
				postfix.append(BLANK + token);
			
			// Outputs remaining operands
			for (;;)
			{
				if (!isalnum(infix[i + 1])) break;
				i++;
				token = infix[i];
				postfix.append(1, token);
			}
		}
	}

	// Pops out remaining operators in Stack
	for (;;)
	{
		if (opStack.empty()) break;
		topToken = opStack.top();
		opStack.pop();

		if (topToken != '(')
		{
			postfix.append(BLANK + topToken);
		}
		else
		{
			cout << "Error in infix expression\n";
			break;
		}
	}
   return postfix;
}

/*****************************************************
* PRIORITY
* Returns the priority of operators, used to determine
* when to pop or push an exponent
*****************************************************/
int priority(char token)
{
	if (token == '(')
		return 0;
	if (token == '+' || token == '-')
		return 1;
	if (token == '*' || token == '/')
		return 2;

	return 3;
}

/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << "\tpostfix: " << postfix << endl << endl;
      }
   }
   while (input != "quit");
}

/**********************************************
 * CONVERT POSTFIX TO ASSEMBLY
 * Convert postfix "5 2 +" to assembly:
 *     LOAD 5
 *     ADD 2
 *     STORE VALUE1
 **********************************************/
string convertPostfixToAssembly(const string & postfix)
{
   // Used for assembly language appending
   string assembly, rhs, lhs, appending;
	char valueNum = '1';

	// Used for string splits
	string str(postfix);		// String to be split
	string buf;					// Buffer string
	stringstream ss(str);	// Loads string into future buffer
	vector <string> tokens;	// Stores split string

	Stack <string> operandStack; // Stack for operands

	// Splits the strings and adds to vector
	while (ss >> buf)
		tokens.push_back(buf);
	
	// Iterate through the split strings
	for (vector<string>::iterator it = tokens.begin(); it < tokens.end(); it++)
	{
		// Later on used for appending the register number
		string value = "VALUE";

		switch (it[0][0])
		{
		case '^':
		case '*':
		case '/':
		case '+':
		case '-':
			// If operator spotted, pop 2 variables
			rhs = operandStack.top();
			operandStack.pop();
			lhs = operandStack.top();
			operandStack.pop();

			// Display load
			assembly.append("\tLOAD ");
			assembly.append(lhs);
			assembly.append(1, '\n');

			// Display operator
			assembly.append(tokenToOperator(it[0][0]));
			assembly.append(rhs);
			assembly.append(1, '\n');

			// Store value and increase value #
			assembly.append("\tSTORE ");
			assembly.append("VALUE");
			assembly.append(1, valueNum);
			assembly.append(1, '\n');
			value.append(1, valueNum);
			operandStack.push(value);
			valueNum++;

			break;
		default:
			// Store operands by default
         operandStack.push(*it);
		}
	}
   return assembly;
}

/*****************************************************
* TOKEN TO OPERATOR
* Accepts a token, and returns assembly language
*****************************************************/
string tokenToOperator(const char token)
{
	switch (token)
	{
	case '^': return "\tEXPONENT "; break;
	case '*': return "\tMULTIPLY "; break;
	case '/': return "\tDIVIDE "; break;
	case '%': return "\tMODULUS "; break;
	case '+': return "\tADD "; break;
	case '-': return "\tSUBTRACT "; break;
	default:
		return "";
		break;
	}
}

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly()
{
   string input;
   cout << "Enter an infix equation.  Type \"quit\" when done.\n";
   
   do
   {
      // handle errors
      if (cin.fail())
      {
         cin.clear();
         cin.ignore(256, '\n');
      }
      
      // prompt for infix
      cout << "infix > ";
      getline(cin, input);
      
      // generate postfix
      if (input != "quit")
      {
         string postfix = convertInfixToPostfix(input);
         cout << convertPostfixToAssembly(postfix);
      }
   }
   while (input != "quit");
}
