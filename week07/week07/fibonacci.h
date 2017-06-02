/***********************************************************************
 * Header:
 *    FIBONACCI
 * Summary:
 *    This will contain just the prototype for fibonacci(). You may
 *    want to put other class definitions here as well.
 * Author
 *    <your names here>
 ************************************************************************/

#ifndef FIBONACCI_H
#define FIBONACCI_H

#include "list.h"        // for LIST

// the interactive fibonacci program
void fibonacci();

template <class T>
void display(const List<T> & rhs );


class Fib 
{
private:
   
   List <unsigned int> digits;
   
public:
   
   Fib() {}
   Fib(const unsigned int & t)throw (const char *);
   Fib(const Fib & rhs)    throw (const char *);
   
   //Operator =
   Fib & operator = (const Fib & rhs) throw(const char *);
   
   void add(const Fib & first, const Fib & second);
   
   // insertion and extraction operators
   friend std::ostream & operator << (std::ostream & out, const Fib & fib);
   
};


#endif // FIBONACCI_H

