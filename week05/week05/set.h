/***********************************************************************
* Header:
*    Set
* Summary:
*
* Author
*    Steve Olsen
************************************************************************/

#ifndef SET_H
#define SET_H

#include <cassert>
#include <iostream>
using namespace std;

// forward declaration for SetIterator
template <class T>
class SetIterator;

template <class T>
class SetConstIterator;

/************************************************
 * Set
 * A class that holds stuff
 ***********************************************/
template <class T>
class Set
{
public:
   // default constructor : empty and kinda useless
   Set() : numItems(0), cap(0), data(NULL) {}

   // copy constructor : copy it
   Set(const Set & rhs) throw (const char *);

   // non-default constructor : pre-allocate
   Set(int capacity) throw (const char *);

   // destructor : free everything
   ~Set()        { if (cap) delete [] data; }

   // is the Set currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Set
   void clear()        { numItems = 0;                 }

   // how many items are currently in the Set?
   int size() const    { return numItems;              }

	 // how big can the Set be?
	 int capacity() { return cap; 				}

   // add an item to the Set
   void insert(const T & t) throw (const char *);

   // deletes an item from the Set
	 void erase(const SetIterator <T> & element) throw (const char *);

   // sorts the Set
   void sort();

   // finds an specific item in the Set
   SetIterator <T> find(const T & t) throw (const char *);

   // return an iterator to the beginning of the Set
   SetIterator <T> begin() { return SetIterator<T>(data); }

   // return an iterator to the end of the Set
   SetIterator <T> end() { return SetIterator<T>(data + numItems);}

   // returns an iterator to the exact end of the Set
   SetIterator <T> end2() { return SetIterator<T>(data + numItems - 1); }

	// operator []
	T& operator [](int index) throw(const char *)
	{
		if ( index < 0 || index > numItems)
			throw " ERROR: Invalid index\n";

		return data[index];
	}
	T& operator [](int index) const throw(const char *)
	{
		if ( index < 0 || index > numItems)
			throw " ERROR: Invalid index\n";

		return data[index];
	}

   // operator =
   Set & operator = (Set <T> & rhs) throw(const char*);

   // return an iterator to the beginning of the Set
   SetConstIterator <T> cbegin() const { return SetConstIterator<T>(data); }

   // return an iterator to the end of the Set
   SetConstIterator <T> cend() const { return SetConstIterator<T>(data + numItems);}

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Set?
   int cap;      // how many items can I put on the Set before full?
};

/**************************************************
 * SET ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class SetIterator
{
  public:
   // default constructor
  SetIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetIterator(T * p) : p(p) {}

   // copy constructor
   SetIterator(const SetIterator & rhs) { *this = rhs; }

   // assignment operator
   SetIterator & operator = (const SetIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   bool operator == (const SetIterator & rhs) const
   {
      return (rhs.p == this->p);
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   SetIterator <T> & operator -- ()
   {
      p--;
      return *this;
   }

   // postfix increment
   SetIterator <T> operator++(int postfix)
   {
      SetIterator tmp(*this);
      p++;
      return tmp;
   }

   SetIterator <T> operator--(int postfix)
   {
      SetIterator tmp(*this);
      p--;
      return tmp;
   }

  private:
   T * p;
};

/**************************************************
 * SET CONST ITERATOR
 * An iterator through set
 *************************************************/
template <class T>
class SetConstIterator
{
  public:
   // default constructor
  SetConstIterator() : p(NULL) {}

   // initialize to direct p to some item
  SetConstIterator(T * p) : p(p) {}

   // copy constructor
   SetConstIterator(const SetConstIterator & rhs) { *this = rhs; }

   // assignment operator
   SetConstIterator & operator = (const SetConstIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const SetConstIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   bool operator == (const SetConstIterator & rhs) const
   {
      return (rhs.p == this->p);
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   SetConstIterator <T> & operator ++ ()
   {
      p++;
      return *this;
   }

   // postfix increment
   SetConstIterator <T> operator++(int postfix)
   {
      SetConstIterator tmp(*this);
      p++;
      return tmp;
   }

  private:
   T * p;
};

/*******************************************
 * Set :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Set <T> :: Set(const Set <T> & rhs) throw (const char *)
{
   assert(rhs.cap >= 0);

   // do nothing if there is nothing to do
   if (rhs.cap == 0)
   {
      cap = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.cap];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.cap);
   cap = rhs.cap;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < cap; i++)
      data[i] = T();
}

/**********************************************
 * Set : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Set to "capacity"
 **********************************************/
template <class T>
Set <T> :: Set(int capacity) throw (const char *)
{
   assert(capacity >= 0);

   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->cap = this->numItems = 0;
      this->data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }

   // copy over the stuff
   this->cap = capacity;
   this->numItems = 0;

   // initialize the Set by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Set :: INSERT
 * Insert an item on the end of the Set
 **************************************************/
template <class T>
void Set <T> :: insert(const T & t) throw (const char *)
{
  SetIterator <T> iInsert = find(t);
  if (iInsert != end())
    return;

  // check buffer
	try
	{
		if (cap == 0 || cap == numItems)
		{
			if (cap == 0)
				cap = 1;
			else
				cap += cap;

			T * temp = new T[cap];

			int index = 0;
			for (SetIterator <T> it = begin(); it != end(); ++it)
				temp[index++] = *it;
			data = temp;
		}
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate a new buffer for Set";
	}

   data[numItems++] = t;
   if (numItems > 1)
   {
     sort();
   }
}

/***************************************************
 * Set :: SORT
 * Sorts items in the Set
 **************************************************/
template <class T>
void Set <T> :: sort()
{
  for(SetIterator <T> j = begin(); j != end2(); ++j)
  {
     for(SetIterator <T> k = end2(); k != j; --k)
     {
       if (*k < *j )
       {
         T temp = *j;
         *j = *k;
         *k = temp;
       }//if end
     }
  }// for end
}

/***************************************************
 * Set :: FIND
 * Finds an item in the Set
 **************************************************/
template <class T>
SetIterator <T> Set <T> :: find(const T & t) throw (const char *)
{/*
  SetIterator <T> iBegin = begin();
  SetIterator <T> iEnd = end();

  while (iBegin != iEnd)
  {
    SetIterator <T> iMiddle = middle();

    if (t == *iMiddle)
      return iMiddle;
    else if (t < *iMiddle)
      iEnd = iMiddle--;
    else
      iBegin = iMiddle++;
  }*/
  for(SetIterator <T> i = begin(); i != end(); ++i)
  {
    if (t == *i)
      return i;
  }
  return end();
}

/***************************************************
 * Set :: ERASE
 * Erases an item in the Set
 **************************************************/
template <class T>
void Set <T> :: erase(const SetIterator <T> & element) throw (const char *)
{
   SetIterator <T> iDelete;

   for (SetIterator <T> i = element; i != end2(); ++i)
   {
     iDelete = i;
     iDelete++;

      *i = *iDelete;
   }

    numItems--;

}

/***************************************************
 * Set :: OPERATOR =
 **************************************************/
template <class T>
Set <T> & Set <T> :: operator = (Set <T> & rhs) throw(const char*)
{
	try
	{
		if(rhs.empty())
			rhs.cap = 1;

		if (rhs.cap == rhs.numItems)
			rhs.cap += 2;

		T * temp = new T[rhs.cap];

		this->data = temp;
		this->cap =rhs.cap;
		this->numItems = rhs.numItems;

		int index = 0;
		for (SetIterator <T> it = rhs.begin(); it != rhs.end(); ++it)
			this->data[index++] = *it;
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate new buffer for Set";
	}

	return *this;
}

/***************************************************
 * OPERATOR && INTERSECTION
 * Retruns all the items two sets have in common.
 **************************************************/
template <class T>
Set <T> operator && (const Set <T> & lhs, const Set <T> & rhs)
{
  int iRHS = 0;
  int iLHS = 0;
  Set <T> setReturn;
  while (iRHS < rhs.size() || iLHS < lhs.size())
  {
    if (iRHS == rhs.size())
      return setReturn;
    else if (iLHS == lhs.size())
        return setReturn;
    else if (lhs[iLHS] == rhs[iRHS])
    {
      setReturn.insert(lhs[iLHS]);
      iRHS++;
      iLHS++;
    }
    else if (lhs[iLHS] < rhs[iRHS])
      iLHS++;
    else
       iRHS++;
  }// while end
  return setReturn;
}

/***************************************************
 * OPERATOR || UNION
 * Returns all the items in two Sets (combines two sets into one)
 **************************************************/
template <class T>
Set <T> operator || (const Set <T> & lhs, const Set <T> & rhs)
{
  int iRHS = 0;
  int iLHS = 0;
  Set <T> setReturn;
  while (iRHS < rhs.size() || iLHS < lhs.size())
  {
    if (iRHS == rhs.size())
      setReturn.insert(lhs[iLHS++]);
    else if (iLHS == lhs.size())
      setReturn.insert(rhs[iRHS++]);
    else if (rhs[iRHS] == lhs[iLHS])
    {
      setReturn.insert(rhs[iRHS]);
      iRHS++;
      iLHS++;
    }
    else if (lhs[iLHS] < rhs[iRHS])
      setReturn.insert(lhs[iLHS++]);
    else
       setReturn.insert(rhs[iRHS++]);

  }// while end
  return setReturn;
}

/***************************************************
 * OPERATOR - DIFFERENCE
 * Returns items in one Sets but not the other
 **************************************************/
template <class T>
Set <T> operator - (const Set <T> & lhs, const Set <T> & rhs)
{
  int iRHS = 0;
  int iLHS = 0;
  Set <T> setReturn;
/*  while (iRHS < rhs.size() || iLHS < lhs.size())
  {
    if (iRHS == rhs.size())
      return setReturn;
    else if (iLHS == lhs.size())
      return setReturn;
    else if (rhs[iRHS] == lhs[iLHS])
    {
      iRHS++;
      iLHS++;
    }
    else if (lhs[iLHS] < rhs[iRHS])
      setReturn.insert(lhs[iLHS++]);
    else
       setReturn.insert(rhs[iRHS++]);

  }// while end   */
  return setReturn;
}

#endif // SET_H
