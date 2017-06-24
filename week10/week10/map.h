/***********************************************************************
 * Component:
 *    Week 09, Binary Search Tree (BST)
 *    Brother Helfrich, CS 235
 * Summary:
 *    This will contain the code for our week10 Map assignment
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef map_h
#define map_h

#include "bst.h"
#include "pair.h"

// Map iterator prototype
template<class K, class V>
class MapIterator;

/************************************************************************
* MAP: Implementation for map with operators and function operations
************************************************************************/
template<class K, class V>
class Map 
{
private:
   int numItems;
   BST <Pair<K, V> > bst;
public:
   // Default constructors
   Map() :  numItems(0), bst() {}
   Map(Map <K, V> &rhs) { *this = rhs; }

   // Index operator
   V & operator [] (const K &key)
   {
      Pair<K, V> pair(key, V());
      BSTIterator<Pair<K, V> > it = bst.find(pair);
      if (it == NULL)
      {
         bst.insert(pair);
         numItems++;
         it = bst.find(pair);
      }
      return it.getNode()->data.second;
   }

   // Assignment operator
   Map<K, V> &operator = (Map<K, V> &rhs) throw (const char*);

   // Getter and setters
   BST<Pair<K, V> > * getBST() { return &bst; }
   int getNumItems() { return numItems; }
   int size() { return numItems; }

   // Operations
   bool empty() { return bst.empty(); }
   void clear() { this->bst.clear(); this->numItems = 0; }
   
   // Iterator functions
   MapIterator<K, V> begin();
   MapIterator<K, V> rbegin();
   MapIterator<K, V> end() { return MapIterator<K, V>(NULL); }
   MapIterator<K, V> rend() { return MapIterator<K, V>(NULL); }

};

/************************************************************************
* INSERTION OPERATOR: Displays the data of a node
************************************************************************/
template <class K, class V>
ostream& operator<< (ostream& out, BinaryNode<Pair<K, V> > d)
{
   // Assures binary node exists
   if (&d != NULL)
   {
      out << d.data.second;
   }
   return out;
}

/************************************************************************
* Assignment Operator: Used for assigning a map to another map
************************************************************************/
template <class K, class V>
Map<K, V> & Map<K, V> ::operator = (Map<K, V> & rhs) throw (const char *)
{
   // clear, then iterate through
   clear();
   if (rhs.bst.begin() != NULL)
   {
         this->bst = rhs.bst;
         this->numItems = rhs.numItems;
   }
   return *this;
}

/************************************************************************
* MAPITERATOR: Class used as an iterator for the Map
************************************************************************/
template <class K, class V>
class MapIterator
{
private:
   BSTIterator <Pair<K, V> > it;
public:
   // Constructors
   MapIterator() : it(NULL) {}
   MapIterator(BinaryNode<Pair<K,V> > * x) { it = x; }
   MapIterator(BSTIterator<Pair<K,V> > x) : it(0) { it = x; }
   MapIterator(const MapIterator<K,V> & rhs) { it = rhs.it; }

   // Copy constructor
   MapIterator(MapIterator<K, V>& cp) { *this = cp; }

   // Operators
   bool operator == (const MapIterator<K, V>& rhs) const
   {
      return rhs.it.operator*() == it.operator*();
   }

   // Not Equal
   bool operator != (const MapIterator<K, V>& rhs) const 
   {
      return this->it.operator!=(rhs.it);
   }

   // Increment
   const MapIterator<K, V>& operator ++()
   {
      ++(this->it);
      return *this;
   }

   // Decrement
   const MapIterator<K, V>& operator --()
   {
      --(this->it);
      return *this;
   }

   // Deference
   const V &operator * ()
   {
      // Dereferences, then calls getSecond function to return V value
      return this->it.operator*().getSecond();
   }
};

/************************************************************************
* MAPITERATOR - BEGIN: This function is used to find the beginning of 
* an iteration
************************************************************************/
template<class K, class V>
MapIterator<K, V> Map<K, V> ::begin()
{
   // Returns BST beginning iteration
   return MapIterator<K, V>(BSTIterator<Pair <K, V> >(bst.begin()));
}

/************************************************************************
* MAPITERATOR - RBEGIN: This function is used for a reverse beginning of
* an iterator
************************************************************************/
template <class K, class V>
MapIterator<K, V> Map<K, V> ::rbegin()
{
   // Returns reverse beginning of BST iterator
   return MapIterator<K, V>(BSTIterator<Pair<K, V> >(bst.rbegin()));
}
#endif /* map_h */
