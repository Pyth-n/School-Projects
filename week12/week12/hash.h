/***********************************************************************
 * Module:
 *    Week 12, Hash Table
 *    Brother Helfrich, CS 235
 * Authors
 *    Jeffry Simpson, David Perez
 * Summary:
 *    This program will implement the Hash Class
 ************************************************************************/
#ifndef HASH_H
#define HASH_H

#include <cassert>
#include "list.h"

template <class T>
class Hash
{
public:
   // Non-default constructor
   Hash(int numBucket) throw (const char *);
   // Copy constructor
   Hash(const Hash<T>& rhs) throw (const char *);
   // Delete constructor
   ~Hash() 
   {
      // clear each element
      for (int i = 0; i < numBucket; i++)
         table[i].clear();

      // delete table
      delete[] table;
   }

   // Hash functions //
   bool empty() { return m_Size == 0; }  // True if no data is stored
   int size() { return m_Size; }         // Returns number of items
   int capacity() const { return numBucket; }// Returns number of buckets (capacity)
   void clear();
   bool find(T e);
   void insert(T e);

   // Virtual hash function
   virtual int hash(const T & value) const = 0;
   
   // Assignment operator
   Hash<T>& operator=(const Hash<T> &rhs)
   {
      clear();
      this->numBucket = rhs.numBucket;
      this->m_Size = rhs.m_Size;
      this->table = new List<T>[numBucket];

      for (int i = 0; i < numBucket; i++)
         this->table[i] = rhs.table[i];

      return *this;
   }


private:
   int numBucket;
   int m_Size;
   List<T>* table;
};


#endif 

// Non-default constructor
template<class T>
Hash<T>::Hash(int numBucket) throw(const char *)
{
   try
   {
      this->numBucket = numBucket;
      m_Size = 0;
      table = new List<T>[numBucket];
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate memory for the hash";
   }
}

// Copy constructor
template<class T>
Hash<T>::Hash(const Hash<T>& rhs) throw(const char *)
{
   try
   {
      this->numBucket = rhs.numBucket;
      this->m_Size = rhs.m_Size;
      this->table = new List<T>[numBucket];

      // Copy contents of table
      for (int i = 0; i < numBucket; i++)
      {
         // Is table allocated?
         if (&rhs.table != NULL)
            table[i] = rhs.table[i];
      }
   }
   catch (std::bad_alloc)
   {
      throw "ERROR: unable to allocate memory for the hash";
   }
}

// Returns number of buckets (capacity)
template<class T>
void Hash<T>::clear()
{
   if (!empty())
   {
      // Loop through table and clear
      for (int i = 0; i < numBucket; i++)
         table[i].clear();

      m_Size = 0;
   }
}

template<class T>
bool Hash<T>::find(T e)
{
   // Get hashed
   int hashed = hash(e);
   assert(hashed >= 0 && hashed < numBucket);

   // Makes sure it's 0 or greater and less than the number of buckets
   if (hashed >= 0 && hashed < numBucket)
   {
      ListIterator<T> it;
      for (it = table[hashed].begin(); it != table[hashed].end(); ++it)
      {
         if (*it == e)
            return true;
      }
   }
   else
      return false;
}

template<class T>
void Hash<T>::insert(T e)
{
   int hashed = hash(e);
   assert(hashed >= 0 && hashed < numBucket);
   if (hashed >= 0 && hashed < numBucket)
   {
      table[hashed].push_back(e);
      m_Size++;
   }
}
