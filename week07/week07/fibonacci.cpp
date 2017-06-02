/***********************************************************************
 * Implementation:
 *    FIBONACCI
 * Summary:
 *    This will contain the implementation for fibonacci() as well as any
 *    other function or class implementations you may need
 * Author
 *    <your names here>
 **********************************************************************/

#include <iostream>
#include "fibonacci.h"   // for fibonacci() prototype
#include "list.h"        // for LIST
using namespace std;


/************************************************
 * FIBONACCI
 * The interactive function allowing the user to
 * display Fibonacci numbers
 ***********************************************/
void fibonacci()
{
   // show the first serveral Fibonacci numbers
   int number;
   cout << "How many Fibonacci numbers would you like to see? ";
   cin  >> number;
   
   
   // your code to display the first <number> Fibonacci numbers
   {

     Fib first(0), second(1), next;       //Create 3 Fib objects
      

      for (int c = 1; c < number+1 ; c++ )
      {
         if ( c <= 1 )
            next = second;
         else
         {
            next.add(first,second);          //Add the two Fibonacci numbers
            first = second;                  //increment up
            second = next;
         }
         
         cout <<"\t"<< next << endl;         //Display output for each loop
         
      }
      
   }


   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   {

     Fib first(0), second(1), next;       //Create 3 Fib objects
  
  
      for (int c = 1; c < number+1 ; c++ )
      {
         if ( c <= 1 )
            next = second;
         else
         {
            next.add(first,second);
            first = second;
            second = next;
         }
         
      }
      
      cout <<"\t"<< next << endl;        //display final number at the end.
  
   }

}


/*******************************************
 *    Fib Non-Default Constructor
 *
 *******************************************/
Fib::Fib(const unsigned int & t)throw (const char *)
{
   digits.push_front(t);
  
}


/*******************************************
 * Fib Copy Constructor
 *  calls the = operator
 *******************************************/
Fib::Fib(const Fib & rhs)    throw (const char *)
{
   *this = rhs;
}


/*******************************************
 * Fib :: = Operator
 *  calls the List Assignment Operator
 *******************************************/
Fib & Fib::operator = (const Fib & rhs) throw(const char *)
{
   
   this->digits = rhs.digits;
   
   return *this;
}

/*******************************************
 * Fib :: Add
 *    Add two link lists (simple)
 *******************************************/

void Fib::add(const Fib & f, const Fib & s)
{
   List <unsigned int> first(f.digits), second(s.digits);  //List to work with
   ListIterator <unsigned int> it1, it2, it3;             //Iterators for the lists
   unsigned int sum=0,carryover=0;                        //addition variables
   
   it1 = first.rbegin();
   it2 = second.rbegin();
   it3 = this->digits.rbegin();
   
   for (; it1 != first.rend(); it1--, it2--)
   {
      sum = *it1 + *it2 + carryover;                  //add up the node + carryover
      
      if(sum > 999)                                   //see if we have carryover
      {
         carryover = (sum * .001);                    //get the carryover for next Node
         sum = sum % 1000;                            //remove carryover
      }
      else
         carryover = 0;                               //reset
      
      *it3-- = sum;                                   //assign value to this node
      
   }
   
   
   if(it2 != second.rend())                           //check if second # is one node bigger  (2nd will always be bigger first)
   {
      sum = *it2 + carryover;                         //if it is add the numbers
      
      *it3 = sum;                                     //assign value to this node
      carryover = 0;                                  //reset
      
   }
   
if(carryover > 0)                                     //means we have carryover we haven't assigned
      this->digits.push_front(carryover);             //create a new node

   
}


/*******************************************
 * Friend streaming In function
 *
 *******************************************/
ostream & operator << (ostream & out, const Fib & fib)
{
   Fib local(fib);
   ListIterator<unsigned int> it;
   
   for (it = local.digits.begin(); it != local.digits.end(); ++it)
   {
      
      if(it != local.digits.begin())
      {
         if(*it < 99)
            out << ",0" << *it;        //zero padding and comma deliminator
         else
             out << "," << *it;        //common deliminator
      }
      else
         out << *it;
      
   }

   return out;
}





