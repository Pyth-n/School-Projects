//
//  problemsets.hpp
//  Week01
//
//  Created by Jeffry Simpson on 4/22/17.
//  Copyright © 2017 Jeffry Simpson. All rights reserved.
//

#ifndef problemsets_hpp
#define problemsets_hpp

#include <stdio.h>
#include <iostream>       // for CIN and COUT
#include <cassert>

/*******************************************************************
 Problem 1:
 Define a class to store a GPA. 
 The class will have a getter called Gpa::get(),
 a setter called Gpa::set() which will validate in the input, 
 a default constructor setting the value to 0.0 a
 nd a single member variable.
 
 *******************************************************************/

class Gpa
{
private:
   
   double m_gpa;

   
public:
   
   //Default Constructor
   Gpa() : m_gpa(0.0){}
   
   const double getter()   {return m_gpa;}

   void mygps(double gpa);
};


//Set Function
void Gpa::mygps(double gpa)
{
   assert(gpa >= 0.0 && gpa <= 4.0);
   m_gpa = gpa;
}



/*******************************************************************
 Problem 2 - 9:
 Use a Time Class.
 
 *******************************************************************/

class Time
{
private:
   int myHours, myMinutes;
   char myAMorPM;
   
   void add(int minutes);
   
public:
   //default constructor
   Time() : myHours(0), myMinutes(0), myAMorPM(NULL) {}
   
   //Copy constructor
   Time(const Time &t1)
   {
      myHours = t1.myHours;
      myMinutes= t1.myMinutes;
      myAMorPM = t1.myAMorPM;
   }
   
   Time(int hours=0, int minutes=0, bool isAM)
   : myHours(hours), MyMinutes(minutes), myAMorPM(isAM ? 'A' : 'P') {}
   
   void display() const
   {
      std::cout << myHours << ' '
      << (myMinutes < 10 ? "0" : "") << myMinutes
      << ' ' << myAMorPM << ".M.";
   }
   
   void copy(const Time & source)
   {
      this->myHours   = source.myHours;
      this->myMinutes = source.myMinutes;
      this->myAMorPM  = source.myAMorPM;
   }
   
   
   
   // Overloaded methods
   friend std::ostream& operator<<(std::ostream& out, const Time &t1);
   Time& operator= (const Time &time);
   Time& operator+(int minute);
   Time& operator+=(int minute);
   Time& operator++();        //Prefix
   Time& operator++(int);     //postfix
};

std::ostream& operator<< (std::ostream &out, const Time &t1)
{
   
   out << t1.myHours << ' '
   << (t1.myMinutes < 10 ? "0" : "") << t1.myMinutes
   << ' ' << t1.myAMorPM << ".M.";
   
   return out;
}

Time& Time::operator=(const Time &source)
{
   // self-assignment guard
   if (this == &source)
      return *this;
   
   this->myHours   = source.myHours;
   this->myMinutes = source.myMinutes;
   this->myAMorPM  = source.myAMorPM;
   
   return *this;
}

void Time::add(int minutes)
{
   myMinutes += minutes;
}

Time& Time::operator+(int minutes)
{
   add(minutes);
   
   return *this;
}


Time& Time::operator+=(int minutes)
{
   add(minutes);
   
   return *this;
}

//Prefix ++
Time& Time::operator++()
{
   myMinutes++;
   return *this;
}

//Postfix ++
Time& Time::operator++(int)
{
   myMinutes++;
   return *this;
}




/*******************************************************************
 Problem 10:
 Write a function to swap two values. These values could be of any data-type.
 
 *******************************************************************/
template <typename T>
void swap(T &t1, T &t2)
{
   T tTmp;
   
   tTmp = t1;
   t1=t2;
   t2=t1;
}

/*******************************************************************
 Problem 11:
 Write a class to store a single value. The value can be of any data-type.
 
 *******************************************************************/
template <class T>
class Store
{
private:
   T m_Value;
   
public:
   //Defaut constructor
   Store () m_Value(NULL) {}
   
   //Non-default Constructor
   Store(T value)
   {
      m_Value = value;
   }
   
   //Copy Constructor
   Store(const T &t1)
   {
      m_Value = t1.m_Value;
   }
   
   T get () const{ return m_Value;}
   void set (T value) { m_value = value; }
   
   
   
};


#endif /* problemsets_hpp */
