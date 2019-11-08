/***********************************************************************
* Header:
*    Go Fish
* Summary:
*    This will contain just the prototype for the goFish() function
* Author
*    Jeffry Simpson, David Perez 
************************************************************************/

#ifndef GO_FISH_H
#define GO_FISH_H
#include "card.h"

#define LINUX
//#define MAC_XCODE
//#define WIN_VISUAL_STUDIO

#ifdef MAC_XCODE
#define CARD_FILE "hand.txt"
#endif // MAC_XCODE

#ifdef WIN_VISUAL_STUDIO
#define CARD_FILE "hand.txt"
#endif // WIN_VISUAL_STUDIO

#ifdef LINUX
#define CARD_FILE "/home/cs235/week05/hand.txt"
#endif // LINUX


#define ROUNDS 5


/**************************************************
 * GO FISH
 * Play the game of "Go Fish"
 *************************************************/
void goFish();

bool readFromFile(Set<Card> & Hand, const string fileName);



#endif // GO_FISH_H

