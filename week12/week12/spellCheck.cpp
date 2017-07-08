/***********************************************************************
 * Module:
 *    Week 12, Spell Check
 *    Brother Helfrich, CS 235
 * Author:
 *    <your name here>
 * Summary:
 *    This program will implement the spellCheck() function
 ************************************************************************/

#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include "spellCheck.h"

using namespace std;


/*****************************************
 * SPELL CHECK
 * Prompt the user for a file to spell-check
 ****************************************/
void spellCheck()
{
   string fileName;
   SHash sHashTable(1);
   vector <string> sMisspelled;
   
   
   //buildHash(sHashTable,"dictionary.txt");                   //local on the mac
   buildHash(sHashTable,"/home/cs235/week12/dictionary.txt");  //for linux lab
   
   cout << "What file do you want to check? ";
   cin  >> fileName;
   
   compareWords(sHashTable, sMisspelled, fileName);
   
   if(sMisspelled.size() > 0)
   {
      cout << "Misspelled: ";
      for(int i=0; i < sMisspelled.size(); i++)
      {
         if(i > 0)
            cout <<", ";
         cout << sMisspelled[i];
      }
      
      cout << endl;
   }
   else
   {
      cout << "File contains no spelling errors\n";
   }
   
}


/************************************************
 * buildHash
 * Get input from text file and put it into the HashTable
 ***********************************************/
void buildHash(SHash & sHashTable, const string & fileName)
{
   string stringInput;              //Hold each word from file
   
   ifstream fin(fileName);          //Open file and check it did.
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return;
   }
   
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> stringInput;           //Get next word
      
      if (fin.eof())
         return;
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return;
      }
      else
         sHashTable.insert(stringInput);      //Hash value added to table from input string
      
   }  //End while Loop
   
}

/************************************************
 * compareWords
 * Compare words in a file to items in the hashtable
 ***********************************************/
void compareWords(SHash sHashTable, vector <string> & misspelled, const string & fileName)
{
   string sCompare,sOriginal;              //Used to hold original and compared word
   
   ifstream fin(fileName);          //Open file
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return;
   }
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> sOriginal;           //Get next word
      
      if (fin.eof())
      {
         return;
      }
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return;
      }
      else
      {
         sCompare = sOriginal;
         std::transform(sCompare.begin(), sCompare.end(), sCompare.begin(), ::tolower);  //Convert word to lowercase
         if(!sHashTable.find(sCompare))            //See if found the value in the hash table
            misspelled.push_back(sOriginal);      //if not, add value to Misspelled words
         
      }
      
   } //End While Loop
   
   
}



// ********************   Testing functions   ***********************


/************************************************
 * HashCheck
 * Quick proceedural funciton to build and check hash functions
 ***********************************************/
void HashCheck()
{
   vector <int> table;
   int iDupCnt, iDups,iMaxDup, iUnique;
   
   
   iDupCnt = iDups = iMaxDup = iUnique = 0;
   
   readFromFile(table,"dictionary.txt");
   
   sort (table.begin(), table.end());
   
   for(int i = 0; i < table.size(); i++, iUnique++)
   {
      // cout << i+1 <<". - " << table[i] << endl;
      cout << table[i];
      iDupCnt=1;
      while(table[i+1] == table[i] )
      {
         iDupCnt++;
         i++;
      }
      if(iDupCnt > 1)
      {
         if(iDupCnt > iMaxDup)
            iMaxDup = iDupCnt;
         cout << "\t" << iDupCnt <<endl;
         iDups++;
      }
      else
         cout << endl;
      
   }
   
   cout << "Unique integters = " << iUnique << " out of " << table.size() << endl;
   cout << "Duplicate integters = " << iDups << " out of " << table.size() << endl;
   cout << "Max Dups = " << iMaxDup << endl;
   cout << "Total Space = 0 to " << table[0] << " to "  << table[table.size()-1] << endl;
}



/************************************************
 * readFromFile
 * Get input from text file and put it into the hashstable
 ***********************************************/

void readFromFile(vector <int> & counts, const string & fileName)
{
   string stringInput;              //Words from file
   
   ifstream fin(fileName);          //Open file
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return;
   }
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> stringInput;           //Get next word
      
      if (fin.eof())
      {
         return;
      }
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return;
      }
      else
      {
         counts.push_back(myHash(stringInput));      //hash file
         
      }
      
   }
   
}

/************************************************
 * Hash function controller to try different hash functions
 * Get input from text file and put it into the map
 ***********************************************/
int myHash(string strInput)
{
   int iHash=-1;
   
   iHash = myHash1(strInput);
   //iHash = myHash2(strInput);
   //iHash = abs((int)djb2Hash(strInput));
   
   
   return iHash;
}

/************************************************
 * Ascii Sum of digits
 * Get input from text file and put it into the map
 ***********************************************/

int SumDigits (string strInput)
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

/************************************************
 * myHash2
 * Get input from text file and put it into the map
 ***********************************************/
int myHash2(string strInput)
{
   int iHash=-1;
   int RandNum;
   
   //hashValue = SumDigits(x);
   RandNum = ((25173 * SumDigits(strInput)) + 13849) % 65536;
   iHash = RandNum % 500;
   
   
   return iHash;
   
}

/************************************************
 * myHash1
 * Get input from text file and put it into the map
 ***********************************************/
int myHash1(string strInput)
{
   int iHash=-1;
   
   iHash = SumDigits(strInput);
   
   
   return iHash;
   
}




/************************************************
 * djb2Hash
 * https://softwareengineering.stackexchange.com/questions/49550/which-hashing-algorithm-is-best-for-uniqueness-and-speed
 ***********************************************/

unsigned long djb2Hash(string strInput)

{
   unsigned long ulHash = 5381;
   int index = 0;
   int strLen = (int)strInput.length();
   
   while (index < strLen)
   {
      char c = strInput[index++];
      ulHash = ((ulHash << 5) + ulHash) + c; /* hash * 33 + c */
   }
   
   return ulHash;
}
