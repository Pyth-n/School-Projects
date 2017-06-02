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

 /*  {
      Fib first(610);
      Fib second(987);
      Fib next(0);
      
      for ( int c = 1 ; c < 12 ; c++ )
      {
         next.add(first,second);
         first = second;
         second = next;
         cout << next << endl;
         
      }
      
   } */
   
   
   {   // your code to display the first <number> Fibonacci numbers

     Fib first(0);
     Fib second(1);
     Fib next(2);
      

      for ( int c = 1 ; c < number+1 ; c++ )
      {
         if ( c <= 1 )
            next = second;
         else
         {
   //         if(c == number)
    //           cout << "pause\n";
            
            next.add(first,second);
            first = second;
            second = next;
         }
         
         cout <<"\t"<< next << endl;
         
      }
      
   }


   // prompt for a single large Fibonacci
   cout << "Which Fibonacci number would you like to display? ";
   cin  >> number;

   // your code to display the <number>th Fibonacci number
   {

      Fib first(0);
      Fib second(1);
      Fib next(2);
  
  
      for ( int c = 1 ; c < number+1 ; c++ )
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
      
       cout <<"\t"<< next << endl;

  
   }



}


/*******************************************
 * Fib Non-Default Constructor
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
 * Fib :: += Operator
 *
 *******************************************/
Fib & Fib::operator += (const Fib & rhs)
{
   cout << "nothing here";
   
   return *this;
}

/*******************************************
 * Fib :: + Operator
 *
 *******************************************/
Fib & Fib::operator + (const Fib & rhs)
{
   
   return *this;
}

/*******************************************
 * Fib :: Add
 *    Add two link lists (simple)
 *******************************************/

void Fib::add(const Fib & f, const Fib & s)
{
   unsigned int sum=0,carryover=0;
   List <unsigned int> first(f.digits), second(s.digits);
   ListIterator <unsigned int> it1, it2, it3;
   
   it1 = first.rbegin();
   it2 = second.rbegin();
   it3 = this->digits.rbegin();
   
   for (; it1 != first.rend(); it1--, it2--)
   {
      sum = *it1 + *it2 + carryover;
      
      if(sum > 999)
      {
         carryover = (sum * .001);  //get the carryover for next
         sum = sum % 1000;
      }
      else
         carryover = 0;
      
      *it3-- = sum;
      
   }
   
   if(it2 != second.rend())
   {
      sum = *it2 + carryover;
      
      *it3 = sum;
      carryover = 0;
      
      
   }
   
if(carryover > 0)
      this->digits.push_front(carryover);


   
}




/*******************************************
 * Fib :: Clear
 *    Clear the Fib lists
 *******************************************/
void Fib::clear()
{
   this->digits.clear();
}

/*******************************************
 * Fib :: Friend streaming In function
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
            out << ",0" << *it;      //zero padding
         else
             out << "," << *it;
      }
      else
         out << *it;
      
   }
   
 /*while(!local.digits.empty())
  {
   
     out << local.digits.front();
     local.digits.pop_front();
  }*/
   
   return out;
}





