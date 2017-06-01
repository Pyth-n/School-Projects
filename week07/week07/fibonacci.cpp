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

   {
      Fib first(610);
      Fib second(987);
      Fib next(0);
      
      next.add(first,second);
      cout << next;
      
   }
   
   
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
            next.add(first,second);
            first = second;
            second = next;
         }
         
         cout << next;
         
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
      
       cout << next;

  
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
   
   do
   {
      sum = first.back() + second.back();
      
      if(sum > 999)
      {
         carryover = sum * .001;  //get the carryover for next
         sum = sum % 1000;
      }
         
         
      
      this->digits.back() = sum;
      
   }while(!first.empty() && !second.empty());
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
   
   while(!local.digits.empty())
   {
   
      out << "\t" << local.digits.front() << endl;
      local.digits.pop_front();
   }
   
   return out;
}




/*  
 
 list2nd.pop_front();
 list1st.push_back(5);
 list1st.push_back(6);
 
 cout << list1.front() << endl;
 list1.front() = list1.front() + list1.back();
 cout << list1.front() << ", " << list1.back() << endl;
 list1.back() = list1.back() - list1.front();
 cout << list1.back() << endl;
 
 
 int first = 0, second = 1, next;
 
 for ( int c = 1 ; c < number+1 ; c++ )
 {
    if ( c <= 1 )
      next = c;
    else
    {
    next = first + second;
    first = second;
    second = next;
    }
 
 cout << next << endl;
 
 }
 
 display(list1);  */
