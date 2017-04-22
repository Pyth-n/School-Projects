/***********************************************************************
* Header:
*    Vector
* Summary:
*    This class contains the notion of a Vector: a bucket to hold
*    data for the user. This is just a starting-point for more advanced
*    constainers such as the vector, set, stack, queue, deque, and map
*    which we will build later this semester.
*
*    This will contain the class definition of:
*        Vector         : A class that holds stuff
*        VectorIterator : An interator through Vector
* Author
*    Br. Helfrich
************************************************************************/

#ifndef VECTOR_H
#define VECTOR_H

#include <cassert>

// forward declaration for VectorIterator
template <class T>
class VectorIterator;

/************************************************
 * Vector
 * A class that holds stuff
 ***********************************************/
template <class T>
class Vector
{
public:
   // default constructor : empty and kinda useless
   Vector() : numItems(0), capacity(0), data(NULL) {}

   // copy constructor : copy it
   Vector(const Vector & rhs) throw (const char *);
   
   // non-default constructor : pre-allocate
   Vector(int capacity) throw (const char *);
   
   // destructor : free everything
   ~Vector()        { if (capacity) delete [] data; }
   
   // is the Vector currently empty
   bool empty() const  { return numItems == 0;         }

   // remove all the items from the Vector
   void clear()        { numItems = 0;                 }

   // how many items are currently in the Vector?
   int size() const    { return numItems;              }

	// how many indices are available in the Vector?
	int numCapacity() const { return capacity; }

   // add an item to the Vector
   void push_back(const T & t) throw (const char *);
   
   // return an iterator to the beginning of the list
   VectorIterator <T> begin() { return VectorIterator<T>(data); }

   // return an iterator to the end of the list
   VectorIterator <T> end() { return VectorIterator<T>(data + numItems);}
   
   // Assignment Operator
	Vector <T> & operator = (const Vector <T> & rhs) throw (const char *);

	// Index operator, non-constant
	T & operator [](int index) throw (const char *);

	// Reallocation method
	T * reallocate(T * oldBuffer, int & size) throw (const char *);

	// Index operator, constant
	const T & operator [](int index) const throw (const char *);

private:
   T * data;          // dynamically allocated array of T
   int numItems;      // how many items are currently in the Vector?
   int capacity;      // how many items can I put on the Vector before full?
};

/**************************************************
 * Vector ITERATOR
 * An iterator through Vector
 *************************************************/
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
   assert(rhs.capacity >= 0);
      
   // do nothing if there is nothing to do
   if (rhs.capacity == 0)
   {
      capacity = numItems = 0;
      data = NULL;
      return;
   }

   // attempt to allocate
   try
   {
      data = new T[rhs.capacity];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: Unable to allocate buffer";
   }
   
   // copy over the capacity and size
   assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capacity);
   capacity = rhs.capacity;
   numItems = rhs.numItems;

   // copy the items over one at a time using the assignment operator
   for (int i = 0; i < numItems; i++)
      data[i] = rhs.data[i];

   // the rest needs to be filled with the default value for T
   for (int i = numItems; i < capacity; i++)
      data[i] = T();
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
      this->capacity = this->numItems = 0;
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
   this->capacity = capacity;
   this->numItems = 0;

   // initialize the Vector by calling the default constructor
   for (int i = 0; i < capacity; i++)
      data[i] = T();
}

/***************************************************
 * Vector :: push_back
 * push_back an item on the end of the Vector
 **************************************************/
template <class T>
void Vector <T> :: push_back(const T & t) throw (const char *)
{
   // do we have space, or is capacity empty?
	if (data == NULL)
	{
		capacity++;

		// Try to allocate
		try
		{
			data = new T[capacity];
		}
		catch (std::bad_alloc)
		{
			throw "Error: Unable to allocate a new buffer for vector";
		}
	}

	// Doubles capacity with reallocate()
	if (capacity == numItems)
	{
		// Doubles and copies content
		data = reallocate(data, capacity);
	}

   // add an item to the end
   data[numItems++] = t;
}

/***************************************************
* Vector :: ASSIGNMENT OPERATOR
* Copies rhs to lhs
**************************************************/
template <class T>
Vector <T> & Vector <T>::operator = (const Vector <T> & rhs) throw (const char *)
{
	assert(rhs.capacity >= 0);

	// Attempt to allocate 
	try
	{
		this->data = new T[rhs.capacity];
	}
	catch (std::bad_alloc)
	{
		throw "ERROR: Unable to allocate buffer";
	}

	// copy over the capacity and size
	assert(rhs.numItems >= 0 && rhs.numItems <= rhs.capacity);
	this->capacity = rhs.capacity;
	this->numItems = rhs.numItems;

	// copy the items over one at a time using the assignment operator
	for (int i = 0; i < numItems; i++)
		this->data[i] = rhs.data[i];

	// the rest needs to be filled with the default value for T
	for (int i = numItems; i < capacity; i++)
		this->data[i] = T();

	return *this;
}

/***************************************************
* Vector :: INDEX OPERATOR
* Accesses index without constant
**************************************************/
template <class T>
T & Vector <T>::operator [](int index) throw (const char *)
{
	if (index >(capacity - 1) || index < 0)
	{
		throw "ERROR: Invalid index";
	}
	else
		return data[index];
}

/***************************************************
* Vector :: INDEX CONSTANT OPERATOR
* Accesses indices constantly
**************************************************/
template <class T>
const T & Vector <T>::operator [](int index) const throw (const char *)
{
	if (index > (capacity - 1) || index < 0)
	{
		throw "ERROR: Invalid index";
	}
	else
		return data[index];
}

/***************************************************
* Vector :: REALLOCATE
* Used for doubling the size of the vector
**************************************************/
template <class T>
T * Vector <T>::reallocate(T * oldBuffer, int & size) throw (const char *)
{
	int oldSize = size;

	// Allocate new buffer
	T * newBuffer = new T[size *= 2];

	// Allocation failure check
	if (NULL == newBuffer)
	{
		size /= 2;
		throw "ERROR: Unable to allocate a new buffer for Vector";
		return oldBuffer;
	}

	// Copy contents
	int i;
	for (i = 0; i < oldSize; i++)
	{
		newBuffer[i] = oldBuffer[i];
	}
	newBuffer[i] = '\0';

	// Delete nasty buffer
	delete[] oldBuffer;

	return newBuffer;
}


#endif // Vector_H