/***********************************************************************
 * Header:
 *    INFIX
 * Summary:
 *    This will contain just the prototypes for the implementation
 * Author
 *    David Donovan, David Perez, Jeffry Simpson
 ************************************************************************/

#ifndef INFIX_H
#define INFIX_H

#include <string>
/*****************************************************
 * TEST INFIX TO POSTFIX
 * Prompt the user for infix text and display the
 * equivalent postfix expression
 *****************************************************/
void testInfixToPostfix();

/*****************************************************
 * TEST INFIX TO ASSEMBLY
 * Prompt the user for infix text and display the
 * resulting assembly instructions
 *****************************************************/
void testInfixToAssembly();

/*****************************************************
* CONVERT INFIX TO POSTFIX
* Algorithm to convert infix input and outputs postfix
*****************************************************/
std::string convertInfixToPostfix(const std::string & infix);

/*****************************************************
* CONVERT POSTFIX TO ASSEMBLY
* Algorithm to convert postfix in assembly language
*****************************************************/
std::string convertPostfixToAssembly(const std::string & postfix);

/*****************************************************
* PRIORITY
* Returns the priority of operators, used to determine
* when to pop or push an exponent
*****************************************************/
int priority(char token);

/*****************************************************
* TOKEN TO OPERATOR
* Accepts a token, and returns assembly language
*****************************************************/
std::string tokenToOperator(const char token);


#endif // INFIX_H

