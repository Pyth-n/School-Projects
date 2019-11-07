/***********************************************************************
* Header:
*    deque.h
* Summary:
*    A double ended queue.
* Author
*    Jeffry Simpson, David Perez
************************************************************************///

#ifndef deque_h
#define deque_h
#include <iostream>
using namespace std;

#include <cassert>

/************************************************
* Deque
* A class that holds our Deque
***********************************************/
template <class T>
class Deque
{
private:
   // Deque circular array
   int iAbsoluteFromIRelative(int i) const
   {
      return (i >= 0) ? (i % max) : (max - ((-1 - i) % max) - 1);
   }
   int getIBack()    const { return iAbsoluteFromIRelative(iBack); }
   int getIFront()   const { return iAbsoluteFromIRelative(iFront); }
   void resize(int & newValue) throw(const char *);
   // Member variables
   T * data;
   int max, iFront, iBack;
public:
   //Constructors
   Deque() : data(NULL), max(0), iFront(0), iBack(-1) {}
   Deque(int capacity)           throw (const char *);
   Deque(const Deque<T> & rhs)   throw (const char *);
   ~Deque() { if (!empty()) delete[] data; }

   //Operator =
   Deque <T> & operator = (const Deque <T> & rightHandSide) throw(const char *);

   //Inline functions
   bool empty()   const { return size() == 0; }
   int size()     const { return iBack - iFront + 1; }
   int capacity() const { return max; }
   void clear() { iFront = 0, iBack = -1; }

   // Unique deque functions
   void push_back(const T & t)   throw(const char *);
   void push_front(const T & t)  throw(const char *);
   void pop_back()               throw(const char *);
   void pop_front()              throw(const char *);

   // Front & back Getters
   T & front() throw(const char *);
   T & back()  throw(const char *);
   T front()   const throw(const char *);
   T back()    const throw(const char *);
};

/*******************************************
* Deque :: Non-Default Constructor
*******************************************/
template <class T>
Deque  <T>::Deque(int capacity) throw(const char *)
{
   assert(capacity > 0);
   // Set custom capacity
   max = capacity;
   data = new T[capacity];

   // If allocated, start default values
   if (data != NULL)
   {
      clear();
   }
}

/*******************************************
* Deque :: Copy Constructor
*******************************************/
template <class T>
Deque <T>::Deque(const Deque & original) throw(const char *)
{
   // Default front and back. Allocate
   clear();
   if (data == NULL)
      max = 2;
   max = original.max;
   data = new T[max];

   // Copy
   int j = 0;
   for (int i = original.iFront; i <= original.iBack; i++)
   {
      iBack++;
      data[j++] = original.data[iAbsoluteFromIRelative(i)];
   }
}

/*******************************************
* Deque :: Operator =
*******************************************/
template <class T>
Deque <T> & Deque <T>::operator=(const Deque <T> & rightHandSide) throw(const char *)
{
   if (this != &rightHandSide)                // check that not st = st
   {
      // Default front and back. Allocate
      clear();
      if (data == NULL)
         max = 2;
      max = rightHandSide.max;
      data = new T[max];

      // Copy
      int j = 0;
      for (int i = rightHandSide.iFront; i <= rightHandSide.iBack; i++)
      {
         data[j++] = rightHandSide.data[iAbsoluteFromIRelative(i)];
         iBack++;
      }
   }
   return *this;
}

/*******************************************
* Deque :: push_back()
*          Add content to back of deque
*******************************************/
template <class T>
void Deque <T>::push_back(const T & t)   throw(const char *)
{
   // NULL CHECK
   if (data == NULL)
   {
      max = 2;
      data = new T[max];
   }

   // Reallocate if full
   if (size() == capacity())
      resize(max);

   // Push to back
   iBack++;
   data[getIBack()] = t;
}

/*******************************************
* Deque :: push_front()
*          Add content to front of deque
*******************************************/
template <class T>
void Deque<T>::push_front(const T & t)   throw(const char *)
{
   // NULL CHECK
   if (data == NULL)
   {
      max = 2;
      data = new T[max];
   }

   // Reallocate if full
   if (size() == capacity())
      resize(max);

   // Push to front
   iFront--;
   data[getIFront()] = t;
}

/*******************************************
* Deque :: pop_back()
*          Remove from back
*******************************************/
template <class T>
void Deque<T>::pop_back()               throw(const char *)
{
   if (empty())
   {
      throw "ERROR: unable to pop from the back of empty deque";
   }
   else
      iBack--;
}

/*******************************************
* Deque :: pop_front()
*          Remove from front
*******************************************/
template <class T>
void Deque<T>::pop_front()               throw(const char *)
{
   if (empty())
   {
      throw "ERROR: unable to pop from the front of empty deque";
   }
   else
      iFront++;
}

/*******************************************
* Deque :: front()
*          Return the front by reference
*******************************************/
template <class T>
T & Deque<T>::front() throw(const char *)
{
   if (!empty())
      return data[getIFront()];
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

/*******************************************
* Deque :: front()
*          Return the front as copy
*******************************************/
template <class T>
T Deque<T>::front()   const throw(const char *)
{
   if (!empty())
      return data[getIFront()];
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

/*******************************************
* Deque :: back()
*          Return the back by reference
*******************************************/
template <class T>
T & Deque<T>::back() throw(const char *)
{
   if (!empty())
      return data[getIBack()];
   else
   {
      throw "ERROR: unable to access data from an empty deque";
   }
}

/*******************************************
* Deque :: back()
*          Return the back by copy
*******************************************/
template <class T>
T Deque<T>::back()   const throw(const char *)
{
   if (!empty())
      return data[getIBack()];
   else
   {
      return "ERROR: unable to access data from an empty deque";
   }
}

/***************************************************
* Deque :: resize()
* Used for doubling the size of data
**************************************************/
template <class T>
void Deque<T>::resize(int & newValue) throw (const char *)
{
   assert(newValue > 0);
   int oldMax = newValue;
   int oldIFront = getIFront();

   // Double size
   newValue *= 2;
   T* newData = new T[newValue];

   // Reset head and tail
   clear();

   // Loop through old array into new one
   for (int i = 0; i < oldMax; i++)
   {
      int index = (i + oldIFront) % oldMax;
      iBack++;
      newData[getIBack()] = data[index];
   }

   // Cleanup
   delete[] data;
   data = newData;
}

#endif /* Deque_h */
