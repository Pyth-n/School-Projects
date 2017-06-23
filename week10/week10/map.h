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

// Map iterator
template<class K, class V>
class MapIterator;

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
   //void increaseItems{ numItems++; }
   int getNumItems() { return numItems; }
   int size() { return numItems; }

   // Operations
   bool empty() { return bst.empty(); }
   void clear() { this->bst.clear(); this->numItems = 0; }
   
   // Iterators
   MapIterator<K, V> begin();
   MapIterator<K, V> end() { return MapIterator<K, V>(NULL); }
   MapIterator<K, V> rbegin();
   MapIterator<K, V> rend() { return MapIterator<K, V>(NULL); }

};

template <class K, class V>
ostream& operator<< (ostream& out, BinaryNode<Pair<K, V> > d)
{
   if (&d != NULL)
   {
      out << d.data.second;
   }
   return out;
}

// Copy operator
template <class K, class V>
Map<K, V> & Map<K, V> ::operator = (Map<K, V> & rhs) throw (const char *)
{
   clear();
   if (rhs.bst.begin() != NULL)
   {
         this->bst = rhs.bst;
         this->numItems = rhs.numItems;
   }
   return *this;
}

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

   bool operator != (const MapIterator<K, V>& rhs) const 
   {
      return this->it.operator!=(rhs.it);
   }

   const MapIterator<K, V>& operator ++()
   {
      ++(this->it);
      return *this;
   }

   const MapIterator<K, V>& operator --()
   {
      --(this->it);
      return *this;
   }

   const V &operator * ()
   {
      return this->it.operator*().getSecond();
   }
};

template<class K, class V>
MapIterator<K, V> Map<K, V> ::begin()
{
   return MapIterator<K, V>(BSTIterator<Pair <K, V> >(bst.begin()));
}

template <class K, class V>
MapIterator<K, V> Map<K, V> ::rbegin()
{
   return MapIterator<K, V>(BSTIterator<Pair<K, V> >(bst.rbegin()));
}
#endif /* map_h */
