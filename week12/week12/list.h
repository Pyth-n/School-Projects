/***********************************************************************
 * Header:
 *    list.h
 * Summary:
 *    This will contain the code for our week07 List assignment
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef list_h
#define list_h
#include <iostream>
using namespace std;

#include <cassert>

// Iterators prototypes
template <class T>
class ListIterator;
template <class T>
class ListConstIterator;

/************************************************
* Node
* Basic class Node
***********************************************/
template <class T>
class Node
{
public:
   // Member variables
   T data;
   Node <T> * pNext, *pPrev;

   // Constructors
   Node() : data(), pNext(NULL), pPrev(NULL) {}

   Node(const T & t) :data(t), pNext(NULL), pPrev(NULL) {}
};

/************************************************
 * List
 * Class for Linked List
 ***********************************************/
template <class T>
class List
{
private:
   Node <T> * pHead, *pTail;
   int numElements;

public:
   //Constructors
   List() : pHead(NULL), pTail(NULL), numElements(0) {}
   List(const T & t)            throw (const char *);
   List(const List<T> & rhs)    throw (const char *);
   ~List();

   //inLine functions

   bool empty()         { return (numElements== 0);}
   int size()           { return numElements; }
   
   //Operator =
   List <T> & operator = (const List <T> & rightHandSide) throw(const char *);

   //Function definitions
   void clear();
   void pop_back();
   void pop_front();
   void push_back(const T & t)  throw (const char *);
   void push_front(const T & t) throw (const char *);
   T & back()                    throw (const char *);
   T & front()                   throw (const char *);
   T   back()              const throw (const char *);
   T   front()             const throw (const char *);

   // Iterator operations
   ListIterator<T> remove(ListIterator<T> &it) throw(const char *);
   ListIterator<T> insert(ListIterator<T> &it, const T& data) throw(const char *);
   ListIterator<T> begin() { return ListIterator<T>(pHead); }
   ListIterator<T> rbegin() { return ListIterator<T>(pTail); }
   ListIterator<T> end() { return ListIterator<T>(NULL); }
   ListIterator<T> rend() { return ListIterator<T>(NULL); }
};

/*******************************************
 * List :: Non-Default Constructor
 *******************************************/
template <class T>
List <T> ::List(const T & t) throw (const char *)
{
   
   numElements= 0;
   
   try
   {
      pHead = new Node<T>(t);
      pTail = pHead;
      numElements++;

   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/*******************************************
 * List :: Copy Constructor
 *******************************************/
template <class T>
List <T> ::List(const List<T> & givenList) throw (const char *)
{
   numElements = 0;

   //Verify we got something to copy
   if (NULL != givenList.pHead)
   {
      // clear();

      try
      {
         // allocate a new head
         pHead = new Node <T>(givenList.pHead->data);
         numElements++;

         Node <T> * pCurrent = pHead;
         Node <T> * pSource = givenList.pHead;     //create a Node to traverse list


         // loop through the rest of the source linked list
         while (pSource->pNext)
         {
            pSource = pSource->pNext;
            pCurrent->pNext = new Node <T>(pSource->data);
            pCurrent->pPrev = pSource->pPrev;
            pCurrent = pCurrent->pNext;
            numElements++;
         }

         pCurrent->pPrev = pSource->pPrev;
         pTail = pCurrent;

      }
      catch (bad_alloc)
      {
         throw "ERROR: unable to allocate a new node for a list";
      }
   }

}

/**********************************************
 * LIST :: assignment operator
 * Copy one list onto another
 *********************************************/
template <class T>
List <T> & List <T> :: operator = (const List <T> & rhs) throw (const char *)
{
   // erase all the existing elements
   clear();
   
   // now allocate the new nodes
   for (Node <T> * p = rhs.pHead; p; p = p->pNext)
      push_back(p->data); // this could throw
      
      // return the new buffer
      return *this;
} 


/*******************************************
 * List :: Destructor
 *******************************************/
template <class T>
List <T> ::~List()
{
   {

      while (pHead != NULL)
      {
         Node <T> *pDelete = pHead;
         pHead = pHead->pNext;
         delete pDelete;
      }
   }

}

/*******************************************
 * List :: back
 *******************************************/
template <class T>
T & List <T> ::back()  throw (const char *)
{
   if (NULL != pTail)
      return pTail->data;

   throw "ERROR: Empty List";
}

/*******************************************
 * List :: front
 *******************************************/
template <class T>
T & List <T> ::front() throw (const char *)
{
   if (NULL != pHead)
      return pHead->data;

   throw "ERROR: Empty List";
}

/*******************************************
 * List :: CONST back
 *******************************************/
template <class T>
T   List <T> ::back() const throw (const char *)
{
   if (NULL != pTail)
      return pTail->data;

   throw "ERROR: Empty List";
   
}

/*******************************************
 * List :: CONST Front
 *******************************************/
template <class T>
T   List <T> ::front() const throw (const char *)
{
   if (NULL != pHead)
      return pHead->data;
 
   throw "ERROR: Empty List";
   
}

/*******************************************
 * List :: clear
 *  Clears linked List
 *******************************************/
template <class T>
void List <T> ::clear()
{

   while (pHead != NULL)
   {
      Node <T> *pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }

   pTail = pHead;
   numElements = 0;
}


/*******************************************
 * List :: Push_back
 *  Adds a Node to the end of the list
 *******************************************/
template <class T>
void List <T> ::push_back(const T & t) throw (const char *)
{

   try
   {
      Node<T>* pNew = new Node<T>(t);


      // If it's empty
      if (NULL == pHead)
      {
         pHead = pNew;
         pTail = pNew;
         numElements++;

      }
      else
      {
         pTail->pNext = pNew;
         pNew->pPrev = pTail;
         pTail = pNew;
         numElements++;

      }
   }
   catch (bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }


}

/*******************************************
 * List :: Push_front
 *  Adds a node to the front of the list
 *******************************************/
template <class T>
void List <T> ::push_front(const T & t) throw (const char *)
{

   try
   {
      Node<T>* pNew = new Node<T>(t);


      // If it's empty
      if (NULL == pHead)
      {
         pHead = pNew;
         pTail = pNew;
         numElements++;

      }
      else
      {
         pHead->pPrev = pNew;
         pNew->pNext = pHead;
         pHead = pNew;
         numElements++;

      }
   }
   catch (bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }


}

/*******************************************
 * List :: Pop_front
 *  Remove a node from the front of the list
 *******************************************/
template <class T>
void List <T> ::pop_front()
{

   if(pHead)
   {
   
      Node <T> * pDelete = pHead;
      
      pHead = pHead->pNext;
      if(pHead && pHead->pNext)
         pHead->pNext->pPrev = pHead;
      
      delete pDelete;
      numElements--;
      
      if(!pHead)
         pTail = pHead;
   
   }
}


/*******************************************
 * List :: Pop_back
 *  Remove a node from the end of the list
 *******************************************/
template <class T>
void List <T> ::pop_back()
{
   
   if(pTail)
   {
      
      Node <T> * pDelete = pTail;
      
      pTail = pTail->pPrev;
      if(pTail && pTail->pPrev)
         pTail->pPrev->pNext = pTail;
      
      delete pDelete;
      numElements--;
      
      if(!pTail)
         pHead = pTail;
   }
   
   
}

/************************************************
* ListIterator
* Class iterator used for list
***********************************************/
template <class T>
class ListIterator
{
public:
   // Constructors
   ListIterator() : p(NULL) {}
   ListIterator(Node<T>* p) : p(p) {}
   ListIterator(const ListIterator<T>& rhs):p(rhs.p){}

   // Operators
   bool operator==(const ListIterator<T> &rhs) const {
      return rhs.p == this->p;
   }
   bool operator!=(const ListIterator<T> &rhs) const {
      return rhs.p != this->p;
   }
   ListIterator<T> & operator=(const ListIterator<T> &rhs) {
      this->p = rhs.p;
      return *this;
   }

   // Prefix operators
   ListIterator<T> & operator++() {
      p = p->pNext;
      return *this;
   }
   ListIterator<T> & operator--() {
      p = p->pPrev;
      return *this;
   }

   // Postfix operators
   ListIterator<T> & operator++(int postfix) {
      ListIterator<T> before(*this);
      p = p->pNext;
      return before;
   }
   ListIterator<T> & operator--(int postfix) {
      ListIterator<T> before(*this);
      p = p->pPrev;
      return before;
   }

   T & operator*() throw(const char *) {
      if (NULL != this->p)
         return this->p->data;
      else
      {
         throw "Iterator not dereferencable!";
      }
   }
   friend ListIterator<T> List<T>::remove(ListIterator<T> &it) throw(const char *);
   friend ListIterator<T> List<T>::insert(ListIterator<T> &it, const T &data) throw(const char *);
private:
   Node <T>* p;
};

/************************************************
* ListConstIterator
* Class iterator used for list
***********************************************/
template <class T>
class ListConstIterator
{
public:
   // Constructors
   ListConstIterator() : p(NULL) {}
   ListConstIterator(const Node<T>* p): p(p) {}
   ListConstIterator(const ListConstIterator<T>& rhs) : p(rhs.p) {}

   // Operations
   ListConstIterator <T> & operator = (const ListConstIterator <T> & rhs)
   {
      p = rhs.p;
      return *this;
   }
   bool operator == (const ListConstIterator <T> & rhs) const
   {
      return rhs.p == this->p;
   }
   bool operator != (const ListConstIterator <T> & rhs) const
   {
      return rhs.p != this->p;
   }
   // postfix ++
   ListConstIterator <T> operator ++ (int postfix)
   {
      ListConstIterator <T> old(*this);
      assert(p);
      p = p->pNext;
      return old;
   }
   // prefix ++
   ListConstIterator <T> & operator ++ ()
   {
      assert(p);
      p = p->pNext;
      return *this;
   }

   // postfix --
   ListConstIterator <T> operator -- (int postfix)
   {
      ListConstIterator <T> old(*this);
      assert(p);
      p = p->pPrev;
      return old;
   }
   // prefix --
   ListConstIterator <T> & operator -- ()
   {
      assert(p);
      p = p->pPrev;
      return *this;
   }
   // Dereference operator
   T operator * () const
   {
      if (NULL != this->p)
         return this->p->data;
      else
      {
         throw "Iterator not dereferencable!";
      }
   }

private:
   Node<T>* p;
};

/************************************************
* Insert
* Inserts data into the iterator chosen
***********************************************/
template <class T>
ListIterator<T> List<T>::insert(ListIterator<T> &it, const T &data) throw(const char *)
{
   // If list is empty
   if (empty())
   {
      pHead = new Node<T>(data);
      pTail = pHead;
      // Returns pHead (first element in list)
      return begin();
   }
   try {
      // Otherwise, let's put it in place
      Node<T>* pNode = new Node<T>(data);

      // If we're at the end of the list
      if (it == end())
      {
         // Setup the tail
         pTail->pNext = pNode;
         pNode->pPrev = pTail;
         pTail = pNode;
         it = pNode;
      }
      else
      {
         // Setup new node's next and previous
         pNode->pNext = it.p;
         pNode->pPrev = it.p->pPrev;

         // Check tail, assign
         if (pNode->pNext)
            pNode->pNext->pPrev = pNode;
         else
            pTail = pNode;

         // Check head, assign
         if (pNode->pPrev)
            pNode->pPrev->pNext = pNode;
         else
            pHead = pNode;

         it = pNode;
      }
      numElements++;

      return it;
   }
   catch (bad_alloc)
   {
      throw "ERROR: unable to allocate a new node for a list";
   }
}

/************************************************
* ListIterator
* Class iterator used for list
***********************************************/
template<class T>
ListIterator<T> List<T>::remove(ListIterator<T>& it) throw(const char *)
{
   // Default it as NULL
   ListIterator<T> itNext = end();

   if (it == end())
   {
      throw "ERROR: unable to remove from an invalid location in a list";
   }

   // Make sure next is not NULL
   if (it.p->pNext)
   {
      it.p->pNext->pPrev = it.p->pPrev;
      itNext = it.p->pNext;
   }
   else
   {
      pTail = pTail->pPrev;
   }

   // Make sure previous is not NULL
   if (it.p->pPrev)
   {
      it.p->pPrev->pNext = it.p->pNext;
   }
   else
   {
      pHead = pHead->pNext;
   }

   // Delete pointer, decrement size
   delete it.p;
   numElements--;

   // Return next pointed node
   return itNext;
}


#endif /* list_h */
