/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: a bucket to hold
*    data for the user. This is a starting-point of more advanced
*    constainers including this vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich and Jeffry Simpson
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;



/************************************************
 * VECTOR
 * A class that holds stuff
 ***********************************************/

template <class T>
class Vector
{
private:
   T * m_Data;          // dynamically allocated array of T
   int m_NumItems;      // how many items are currently in the Vector?
   int m_Capacity;      // how many items can I put on the Vector before full?
   
public:
   
   // default constructor : empty and kinda useless
   Vector() : m_NumItems(0), m_Capacity(0), m_Data(NULL) {}
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);

   // destructor : free everything
   ~Vector()        { if (m_Capacity) delete [] m_Data; }
   
   // Operator =
  Vector & operator = (const Vector<T> &rhs) throw (const char *);

   //Square Bracket Operator
   T& operator[] (int index) throw(const char *)
   {
      if ( index < 0 || index > m_NumItems)
         throw " ERROR: Invalid index\n";
      
      return m_Data[index];
   }

   //Square Bracket Operator const
   const T operator[] (int index) const throw (const char *)
   {
      if ( index < 0 || index > m_NumItems)
         throw " ERROR: Invalid index\n";
      
      return m_Data[index];
   }

   
   // how many items are currently in the Vector?
   int size()     const    { return m_NumItems;          }
   
   // how many items can the Vector hold?
   int capacity() const    { return m_Capacity;          }
  
   // is the Vector currently empty
   bool empty()   const    { return m_NumItems == 0;     }

   // remove all the items from the Vector
   void clear()            { m_NumItems = 0;             }
   
   //push_back to add items to end of lists
   void push_back(const T & t) throw (const char *);

   // add an item to the Vector
   void insert(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(m_Data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(m_Data + m_NumItems);}
   
};



/************************************************
 * Vector ITERATOR
 * An iterator through Vector
 ***********************************************/

template <class T>
class VectorIterator
{
  public:
   // default constructor
  VectorIterator() : p(NULL) {}

   // initialize to direct p to some item
  VectorIterator(T * p) : p(p) {}

   // copy constructor
   VectorIterator(const VectorIterator & rhs) { *this = rhs; }

   // assignment operator
   VectorIterator & operator = (const VectorIterator & rhs)
   {
      this->p = rhs.p;
      return *this;
   }

   // not equals operator
   bool operator != (const VectorIterator & rhs) const
   {
      return rhs.p != this->p;
   }

   // dereference operator
   T & operator * ()
   {
      return *p;
   }

   // prefix increment
   VectorIterator <T> & operator ++ ()
   {
      p++;
      return *this;
     
   }

   // postfix increment
   VectorIterator <T> operator++(int postfix)
   {
      VectorIterator tmp(*this);
      p++;
      return tmp;
   }
   
  private:
   T * p;
};


/*******************************************
 * Vector :: COPY CONSTRUCTOR
 *******************************************/
template <class T>
Vector <T> :: Vector(const Vector <T> & rhs) throw (const char *)
{
   assert(rhs.m_Capacity >= 0);
   
   // do nothing if there is no capacity to do anything
   if (rhs.m_Capacity == 0)
   {
      m_Capacity = m_NumItems = 0;
      m_Data = NULL;
      return;
   }
   
   // attempt to allocate
   try
   {
      m_Data = new T[rhs.m_Capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.m_NumItems >= 0 && rhs.m_NumItems <= rhs.m_Capacity);
   m_Capacity = rhs.m_Capacity;
   m_NumItems = rhs.m_NumItems;
   
   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < m_NumItems; i++)
      m_Data[i] = rhs.m_Data[i];
      
      // the rest needs to be filled with the default value for T
      for (int i = m_NumItems; i < m_Capacity; i++)
         m_Data[i] = T();
}


/**********************************************
 * Vector : NON-DEFAULT CONSTRUCTOR
 * Preallocate the Vector to "capacity"
 **********************************************/
template <class T>
Vector <T> :: Vector(int capacity) throw (const char *)
{
   assert(capacity >= 0);
   
   // do nothing if there is nothing to do
   if (capacity == 0)
   {
      this->m_Capacity = this->m_NumItems = 0;
      this->m_Data = NULL;
      return;
   }
   
   // attempt to allocate
   try
   {
      m_Data = new T[capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   
   // copy over the stuff
   this->m_Capacity = capacity;
   this->m_NumItems = 0;
   
   // initialize the Vector by calling the default constructor
   for (int i = 0; i < capacity; i++)
      m_Data[i] = T();
}


/***************************************************
 * Vector :: INSERT
 * Insert an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: insert(const T & t) throw (const char *)
{
   // do we have space?
   if (m_Capacity == 0 || m_Capacity == m_NumItems)
      throw "ERROR: Insufficient space";
   
   // add an item to the end
   m_Data[m_NumItems++] = t;
}


/*******************************************
 * Vector :: Operator =
 
 *******************************************/
template <class T>
Vector<T> & Vector <T> :: operator = (const Vector <T> &rhs)
throw (const char *)
{

   assert(rhs.m_NumItems >= 0 && rhs.m_NumItems <= rhs.m_Capacity);
      
   // do nothing right hand size is empty
   if (rhs.m_Capacity == 0)
   {
      m_Capacity = m_NumItems = 0;
      m_Data = NULL;
      return *this;
   }
   
   //Delete existing data, if any
   if(m_Capacity)
      delete [] m_Data;
   
   //Prep the class for new data
   try
   {
      m_Data = new T[rhs.m_Capacity];
      m_NumItems = rhs.m_NumItems;
      m_Capacity = rhs.m_Capacity;
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy the items over one at a time
   for (int i = 0; i < m_NumItems; i++)
      m_Data[i] = rhs.m_Data[i];
      
   // the rest needs to be filled with the default value for T
   for (int i = m_NumItems; i < m_Capacity; i++)
      m_Data[i] = T();
         
   return *this;
}


/***************************************************
 * Vector :: push_back
 * Add an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
 
   if(!m_Capacity)  //Check for 0 size data
   {
      m_Capacity++;
      try
      {
         m_Data = new T[m_Capacity];
      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }
   }
   
   
   if(m_NumItems >= m_Capacity)  //Check if we need to make it bigger
   {
      try
      {
         Vector <T> vTmp(m_Capacity);              // Create Temp array

         for (int i = 0; i < m_NumItems; ++i)      //Move all the data over
            vTmp.m_Data[i] = m_Data[i];

         delete [] m_Data;                         //Delete the old one
         
         m_Capacity *=2;
         m_Data = new T[m_Capacity];               //Recreate it bigger
         
         for (int i = 0; i < m_NumItems; ++i)      //Copy data back
            m_Data[i] = vTmp.m_Data[i];

      }
      catch (std::bad_alloc)
      {
         throw "ERROR: Unable to allocate buffer";
      }

   }
   
   //assign new items and return
   m_Data[m_NumItems++] = t;
   return;
   
}

#endif // Vector_H

