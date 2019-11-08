/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother Helfrich, CS 235
* Author:
*    <your names here>
* Summary: 
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  0.0 hrs   
*    Actual:     0.0 hrs
*      Please describe briefly what was the most difficult part.
************************************************************************/

#include <iostream>
#include <fstream>
#include <string.h>
#include "set.h"
#include "card.h"
#include "goFish.h"
using namespace std;



/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   Set <Card> myHand;               //Hand Set
   Card card;                       //Current Card
   int matches    = 0,              //Number of Matches
       looper     = 1;              //Looper used for output printing
   SetIterator<Card> ct;            //Set Iterator
   
    
   if(!readFromFile(myHand, CARD_FILE))
      return;                             //Leave if we didn't open the file

   
   cout << "We will play " << ROUNDS <<" rounds of Go Fish.  Guess the card in the hand\n";
   
   for(int i=1; i <= ROUNDS; i++)
   {
      cout << "round " << i <<": ";
      
      cin  >> card;                                //Get User input for Card
      
      ct = myHand.find(card);                      //See if Card is in the Hand
      
      if(ct != myHand.end())
      {
         cout << "\tYou got a match!\n";
         myHand.erase(ct);
         matches++;
      }
      else
      {
         
          cout << "\tGo Fish!\n";
      }
      
   }

   //Output printing
   cout << "You have " << matches << " matches!\n";
   cout << "The remaining cards: ";
   for (SetIterator <Card> it = myHand.begin(); it != myHand.end(); it++)
   {
      cout << *it;
      if(looper++ < myHand.size())
         cout << ", ";
      else
         cout << "\n";
   }

   
   return ;
}

/************************************************
 * readfromFile
 * Get input from text file
 ***********************************************/
bool readFromFile(Set<Card> & Hand, const string fileName)
{
   char * nextCard = nullptr;       //NextCard input
   string stringInput;              //String from file
   
   ifstream fin(fileName);          //Open file
   if (fin.fail())
   {
      cout << "Unable to open file " << fileName << endl;
      return false;
   }
   
   while(!fin.eof())                //While not at End of File
   {
      fin >> stringInput;

      if (fin.eof())
      {
         return true;
      }
      else if (fin.fail())
      {
         cout << "Error reading from file\n";
         return false;
      }
      else
      {
         
         char *cstr = new char[stringInput.length() + 1];      //Create Char variable
         strcpy(cstr, stringInput.c_str());                    //String copy
         Hand.insert(cstr);                                    //Insert string
         delete [] cstr;                                       //Delete Char variable
         
      }
      
   }

   
   return true;
}
