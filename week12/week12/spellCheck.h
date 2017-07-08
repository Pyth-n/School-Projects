/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    Br. Helfrich
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#ifndef SPELL_CHECK_H
#define SPELL_CHECK_H

#include <vector>
#include "hash.h"

using namespace std;


/****************************************
 * String HASH
 * A simple hash of integers
 ****************************************/
class SHash : public Hash <string>
{
public:
//   SHash(): Hash() {}
   SHash(int numBuckets)    throw (const char *) : Hash <string> (numBuckets) {}
   SHash(const SHash & rhs) throw (const char *) : Hash <string> (rhs)        {}
   
   // hash function
   int hash(const string strInput) const;
   
};


/*****************************************
 * Hash :: String hash function
 * Simple hash function that uses the sum of the letters of the stirng.
 
 ****************************************/
int SHash :: hash(const string strInput) const
{
   int index = 0;
   int sum = 0;
   int strLen = (int)strInput.length();
   
   while (index < strLen)
   {
      char character = strInput[index];
      int number = character;
      sum = number + sum;
      index ++;
   }
   return sum;
}



//Used Function defintions

void spellCheck();
void buildHash(SHash & counts, const string & fileName);
void compareWords(SHash sHashTable, vector <string> & misspelled,const string & fileName);


//Testing stuff
void readFromFile(vector <int> & counts, const string & fileName);
void HashCheck();
int myHash(string x);
int SumDigits (string strInput);

//Trial Hashes
int myHash1(string strInput);
int myHash2(string strInput);
unsigned long djb2Hash(string strInput);


#endif // SPELL_CHECK_H
