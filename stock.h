/***********************************************************************
 * Header:
 *    STOCK
 * Summary:
 *    This will contain just the prototype for stocksBuySell(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef STOCK_H
#define STOCK_H

#include "dollars.h"   // for Dollars defined in StockTransaction
#include "queue.h"     // for QUEUE
#include <iostream>    // for ISTREAM and OSTREAM

// the interactive stock buy/sell function
void stocksBuySell();

class Stock
{
public:
   Dollars amount, profit;  //Dollars object
   
   //Constructor
   Stock () : m_Quantity(0), amount(0), profit(0){}
   
   //member functions
   void setQuantity(int quantity)   { m_Quantity = quantity;}
   int  getQuantity()               { return m_Quantity;    }
   
   friend std::ostream & operator << (std::ostream & out, const Stock & rhs);
   friend std::istream & operator >> (std::istream & in,        Stock & rhs);
   
private:
   int m_Quantity;

};



// Menu structure enumeration list
enum eMenu
{
   BUY,
   SELL,
   DISPLAY,
   QUIT,
   MAX_VAL
};

//Menu Function definiton
eMenu string2enum(string word );

#endif // STOCK_H
