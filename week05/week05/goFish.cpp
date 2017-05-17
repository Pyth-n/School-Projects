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
   Set <Card> myHand;
   Card card;
   int matches = 0,
       rounds = 5;
   SetIterator<Card> ct;
   
   
   //Read from File(myHand, filelocaton)
   myHand.insert("Shark");
   myHand.insert("Cod");
   myHand.insert("AngleFish");
   myHand.insert("Crab");
   myHand.insert("Dolphin");
   myHand.insert("SeaHorse");

   
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
   
   for(int i=1; i <= rounds; i++)
   {
      cout << "round " << i <<": ";
      
      cin  >> card;
      
      ct = myHand.find(card);
      
      if(ct != myHand.end())
      {
         cout << "You got a match!\n";
         myHand.erase(ct);
         matches++;
      }
      else
      {
         
          cout << "\tGo Fish!\n";
      }
      
   }

   
   cout << "You have " << matches << " matches!\n";
   cout << "The remaining cards: ";
   for (SetIterator <Card> it = myHand.begin(); it != myHand.end(); it++)
      cout << *it << ", ";

   
   return ;
}

//Read from File()
