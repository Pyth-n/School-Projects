/***********************************************************************
* Program:
*    Assignment 01, Go Fish
*    Brother JonesL, CS 235
* Author:
*    J Aaron Lavold
* Summary:
*    This is all the functions necessary to play Go Fish!
*
*    Estimated:  2.0 hrs
*    Actual:     2.0 hrs
*      Trimming down the lines of code so it was very concise
************************************************************************/

#include <iostream>
#include <iostream>
#include <fstream>
#include <string>
#include "set.h"

#include "card.h"
#include "goFish.h"
//#include <set>
using namespace std;

// Prototypes!
void loadHand(Set<Card> & goFishHand);
void playGame(Set<Card> & goFishHand, int & matchCount);
void displayGameResults(Set<Card> & goFishHand, int & matchCount);
/**********************************************************************
 * GO FISH
 * The function which starts it all
 ***********************************************************************/
void goFish()
{
   // Count of guesses that matched a card in the Hand
   int matchCount = 0;

   //  This set is a collection of Cards that make up the other players Hand
   Set<Card> goFishHand;

   // Calls the function that loads the Hand from a text file
   loadHand(goFishHand);

   // Let's play a game... calls the function that starts game play
   playGame(goFishHand, matchCount);

   // Calls the function that displays the final results of 5 rounds of play
   displayGameResults(goFishHand, matchCount);

   return ;
}

/*****************************
 * loadHand:  This function reads a file containing a Hand of Go Fish and loads it into a set of Cards
 * RETURN:    None
 * PARAMETER: std::set<Card> by reference   goFishHand
 *****************************/
void loadHand(Set<Card> & goFishHand)
{
   //Card goFishCard;
   try
   {
      string handLine;
      ifstream handFile ("/home/cs235/week05/hand.txt");
      if (handFile.is_open())
      {
         while ( getline (handFile,handLine) )
         {
            // loads an array with the data input by student help request
            size_t pos = 0;
            while ((pos = handLine.find(" ")) != std::string::npos)
            {
               goFishHand.insert(handLine.substr(0,pos).c_str());
               handLine.erase(0, pos + 1);
            }
            goFishHand.insert(handLine.c_str());
         }
         handFile.close();
      }
   }
   catch(exception ex)
   {
      cout << "Exception encountered";
   }


}

/*****************************
 * playGame:  Let's play a game... This function is the start of actual game play.
 *                It prompts the player for a Card guess and then responds back letting the
 *                user know if they guessed correctly.  After 5 guess game play is over.
 * RETURN:    None
 * PARAMETER: std::set<Card> by reference    goFishHand -  the other players Go Fish hand
 *            int by reference               matchCount -  a count of correct guesses
 *****************************/
void playGame(Set<Card> & goFishHand, int & matchCount)
{
   cout << "We will play 5 rounds of Go Fish.  Guess the card in the hand\n";
   Card guess;
   for( int i = 1 ; i < 6 ; i++)
   {
      cout << "round " << i << ": ";
      cin >> guess;
      if (goFishHand.find(guess) != goFishHand.end())
      {
         cout << "\tYou got a match!\n";
         goFishHand.erase(goFishHand.find(guess));
         matchCount++;
      }
      else
         cout << "\tGo Fish!\n";
   }
}

/*****************************
 * DisplayGameResults:  Displays two messages. One about the number of matches in the 5 rounds
 *                      and the other a list of Cards still in the other players hand.
 * RETURN:    None
 * PARAMETER: std::set<Card> by reference    goFishHand -  the other players Go Fish hand
 *            int by reference               matchCount -  a count of correct guesses
 *****************************/
void displayGameResults(Set<Card> & goFishHand, int & matchCount)
{
   cout << "You have " << matchCount << " matches!\n";
   cout << "The remaining cards:";
   for(SetIterator<Card> iterator1 = goFishHand.begin(); iterator1 != goFishHand.end(); ++iterator1)
   {
      cout << (iterator1 != goFishHand.begin() ?  ", " : " ");
      cout << *iterator1;
   }
   cout << endl;
}
