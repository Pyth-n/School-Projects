/***********************************************************************
 * Header:
 *    set.h
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
   Node <T> * pNext, * pPrev;
   
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

   Node <T> * pHead, * pTail;
   int numElements;
   
   
public:
   
   //Constructors
   List(): pHead(NULL), pTail(NULL), numElements(0){}
   List(const T & t)            throw (const char *);
   List(List<T> & rhs)    throw (const char *);
   ~List();
   
   
   //inLine functions
   bool empty()         { return (!pHead && !pTail && (numElements== 0));}
   int size()           { return numElements; }
   
   //Operator =
   List <T> & operator = (List <T> & rightHandSide) throw(const char *);
   
   //Function definitions
   void clear();
   void push_back (const T & t)  throw (const char *);
   void push_front (const T & t) throw (const char *);
   T & back()                    throw (const char *);
   T & front()                   throw (const char *);
   T   back()              const throw (const char *);
   T   front()             const throw (const char *);
   
   
};


/*******************************************
 * List :: Non-Default Constructor
 *******************************************/
template <class T>
List <T> ::List(const T & t) throw (const char *)
{
   try
   {
      pHead = new Node<T>(t);
      pTail = pHead;
      numElements++;
      
   }
   catch (bad_alloc)
   {
      throw "ERROR: Can't allocate memory for a Node!";
   }
   
   

}

/*******************************************
 * List :: Copy Constructor
 *******************************************/
template <class T>
List <T> ::List(List<T> & pSource) throw (const char *)
{
   numElements= 0;
   
   //Verify we got something to copy
   if (NULL != pSource.pHead)
   {

      try
      {
         // allocate a new head
         pHead = new Node <T> (pSource.pHead->data);
         numElements++;
         Node <T> * pCurrent = pHead;
        
         
         // loop through the rest of the source linked list
         while (pSource.pHead->pNext)
         {
            pSource.pHead = pSource.pHead->pNext;
            pCurrent->pNext = new Node <T> (pSource.pHead->data);
            pCurrent->pPrev = pSource.pHead->pPrev;
            pCurrent = pCurrent->pNext;
            numElements++;
         }
         
         pCurrent->pPrev = pSource.pHead->pPrev;
         pTail = pCurrent;

      }
      catch (bad_alloc)
      {
         throw "ERROR: Can't allocate memory for a Node!";
      }
   }

}

/*******************************************
 * List :: Operator =
 *******************************************/
template <class T>
List <T> & List <T>::operator=(List <T> & pSource) throw(const char *)
{

   if (this != &pSource)                // check that not st = st
   {
      try
      {
         // allocate a new head
         Node <T> * pDestination = new Node <T> (pSource.pHead->data);
         Node <T> * pCurrent = pDestination;
         
 
         
         // loop through the rest of the source linked list
         while (pSource.pHead->pNext)
         {
            pSource.pHead = pSource.pHead->pNext;
            pCurrent->pNext = new Node <T> (pSource.pHead->data);
            pCurrent->pPrev = pSource.pHead->pPrev;
            pCurrent = pCurrent->pNext;
         }
         
         pCurrent->pPrev = pSource.pHead->pPrev;
         pTail = pCurrent;

         pHead = pDestination;
         

      }
      catch (bad_alloc)
      {
         throw "ERROR: Can't allocate memory for a Node!";
      }
      
   }
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
T & List <T> :: back()  throw (const char *)
{
   if(NULL != pTail)
      return pTail->data;

   throw "ERROR: Empty List";
}

/*******************************************
 * List :: front
 *******************************************/
template <class T>
T & List <T> :: front() throw (const char *)
{
   if(NULL != pHead)
      return pHead->data;

    throw "ERROR: Empty List";
}

/*******************************************
 * List :: CONST back
 *******************************************/
template <class T>
T   List <T> :: back() const throw (const char *)
{
   if(NULL != pTail)
      return pTail->data;
   
}

/*******************************************
 * List :: CONST Front
 *******************************************/
template <class T>
T   List <T> :: front() const throw (const char *)
{
   if(NULL != pHead)
      return pHead->data;
   
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
}


/*******************************************
 * List :: Push_back
 *  Adds a member to the end of the list
 *******************************************/
template <class T>
void List <T> :: push_back(const T & t) throw (const char *)
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
   




#endif /* list_h */
