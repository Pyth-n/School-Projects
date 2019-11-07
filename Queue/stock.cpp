/***********************************************************************
 * Implementation:
 *    STOCK
 * Summary:
 *    This will contain the implementation for stocksBuySell() as well
 *    as any other function or class implementation you need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>    // for ISTREAM, OSTREAM, CIN, and COUT
#include <string>      // for STRING
#include <cassert>     // for ASSERT
#include "stock.h"     // for STOCK_TRANSACTION
#include "queue.h"     // for QUEUE
using namespace std;



/************************************************
 * STOCKS BUY SELL
 * The interactive function allowing the user to
 * buy and sell stocks
 ***********************************************/
void stocksBuySell()
{
   string chooser;                     //Menu chooser input
   eMenu picked;                       //Enum converted from menu chooser
   Stock stockBuy, stockSell;          //Stock objects for BUying and selling
   int totalStock=0;                   //Used to calculate Total stock owned
   Dollars proceeds = 0;               // to calculate total proceeds
   Queue<Stock> buyQue,
               sellQue,
               showQue;             //Queues for Buying, for Selling, and for display
   
   
   // instructions
   cout << "This program will allow you to buy and sell stocks. "
        << "The actions are:\n";
   cout << "  buy 200 $1.57   - Buy 200 shares at $1.57\n";
   cout << "  sell 150 $2.15  - Sell 150 shares at $2.15\n";
   cout << "  display         - Display your current stock portfolio\n";
   cout << "  quit            - Display a final report and quit the program\n";

   
      do
      {
         cin.ignore();
         cin.clear();
         cout << "> ";
         cin >> chooser;                       //Menu options

         picked = string2enum(chooser);         //change string to enum
         
         switch (picked)
         {
            case BUY:
               cin >> stockBuy >> stockBuy.amount;       //get stock input
         
               buyQue.push(stockBuy);                    //push new stock to Buy queue
               totalStock += stockBuy.getQuantity();  //add to total owned
               
               break;
               
            case SELL:
               cin >> stockSell >> stockSell.amount;       //get stock data input

               if(!buyQue.empty())                  //check if we own stock
               {
                  if(stockSell.getQuantity() > totalStock)    //check if we are selling more than we own
                     stockSell.setQuantity(totalStock);      //only sell what we own
                  
                  stockBuy = buyQue.front();                  //Get first item
                  int sellQnty = stockSell.getQuantity();
                  
                  while((sellQnty > stockBuy.getQuantity()) && (totalStock > 0))
                  {
                     stockSell.profit = ((stockSell.amount * stockBuy.getQuantity()) -
                                      (stockBuy.amount * stockBuy.getQuantity()));
                                     
                     stockSell.setQuantity(stockBuy.getQuantity());
                     
                     totalStock -= stockBuy.getQuantity();    //deduce total stock owned
                     sellQnty -= stockBuy.getQuantity();      //reduce selled quanity
                     
                     sellQue.push(stockSell);
                     buyQue.pop();                            //pop off queue
                     stockBuy = buyQue.front();               //get next item
                     
                     stockSell.profit = 0;    //Clean-up at the end
                  }
                  
                  if((sellQnty > 0) && (totalStock > 0))
                  {
                     
                     stockSell.setQuantity(sellQnty);
                     stockSell.profit = ((stockSell.amount * sellQnty) -
                                     (stockBuy.amount * sellQnty));
                     
                     sellQue.push(stockSell);

                     
                     stockBuy.setQuantity(stockBuy.getQuantity() - sellQnty);
                     buyQue.front() = stockBuy;
    
                     //cleanup
                     if(stockBuy.getQuantity() == 0)
                        buyQue.pop();
                     stockSell.profit = 0;
                  }
                  
                  
               } //end if
            
           
               
               break;
               
            case DISPLAY:
              if(!buyQue.empty())
               {
                  showQue = buyQue;              // copy buy so that we can pop with out changing the orginal
                  cout << "Currently held:\n";
                  for(int i=0; i < buyQue.size(); i++)
                  {
                     cout << "\tBought "<< showQue.front() << endl;
                     showQue.pop();
                  }
               }
               
               if(!sellQue.empty())
               {
                  showQue = sellQue;     // making a copy
                  cout << "Sell History:\n";
                  for(int i=0; i < sellQue.size(); i++)
                  {
                     cout << "\tSold "<< showQue.front() << endl;
                     stockSell = showQue.front();
                     proceeds += stockSell.profit;
                     showQue.pop();
                  }
               }
               
               cout << "Proceeds: " << proceeds << endl;
               proceeds = 0;     //clean up at the end

               break;
               
            case QUIT:
               break;
               
            default:
               cout << "\tInvalid option.\n";
         }
      }
      while (picked != QUIT);
   
   
}


/*******************************************
 * Stock :: Friend streaming out function
 *******************************************/
ostream & operator << (ostream & out, const Stock & rhs)
{
   if(rhs.profit == 0)
      out << rhs.m_Quantity << " shares at " <<rhs.amount;
   else
      out << rhs.m_Quantity << " shares at " <<rhs.amount
      << " for a profit of " << rhs.profit;
   
   return out;
}


/*******************************************
 * Stock :: Friend streaming In function
 * Borrowed heavily from Dollor.cpp streaming in function
 *******************************************/
std::istream & operator >> (std::istream & in, Stock & rhs)
{
   rhs.m_Quantity = 0;  //start clean
   
   if (in.fail())
      return in;
   
   while (isspace(in.peek()))   //remove space
      in.get();
   
   while (isdigit(in.peek()))   // Get digits
      rhs.m_Quantity = rhs.m_Quantity * 10 + (in.get() - '0');
   
   return in;
}

/*******************************************
 * string2enum()
 * Function to change input string to output enum
 * for switch statement
 *******************************************/

eMenu string2enum(string word )
{
   for (auto & c: word) c = toupper(c);

   if(word == "BUY")
      return BUY;
   
   if(word == "SELL")
      return SELL;
   
   if(word == "DISPLAY")
      return DISPLAY;
   
   if(word == "QUIT")
      return QUIT;
   
   return MAX_VAL;  //got something else
   
}



