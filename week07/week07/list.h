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
   List(const List<T> & rhs)    throw (const char *);
   ~List();
   
   
   //inLine functions
   bool empty()         { return (!pHead && !pTail && (numElements== 0));}
   int size()           { return numElements; }
   
   //Operator =
   List <T> & operator = (const List <T> & rightHandSide) throw(const char *);
   
   //Function definitions
   void clear();
   void pop_back();
   void pop_front();
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
      throw "ERROR: unable to allocate a new node for a list";
   }
   
   

}

/*******************************************
 * List :: Copy Constructor
 *******************************************/
template <class T>
List <T> ::List(const List<T> & givenList) throw (const char *)
{
   numElements= 0;
   
   //Verify we got something to copy
   if (NULL != givenList.pHead)
   {

      try
      {
         // allocate a new head
         pHead = new Node <T> (givenList.pHead->data);
         numElements++;
         
         Node <T> * pCurrent = pHead;
         Node <T> * pSource = givenList.pHead;     //create a Node to traverse list
        
         
         // loop through the rest of the source linked list
         while (pSource->pNext)
         {
            pSource = pSource->pNext;
            pCurrent->pNext = new Node <T> (pSource->data);
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

/*******************************************
 * List :: Operator =
 *******************************************/
template <class T>
List <T> & List <T>::operator=(const List <T> & givenList) throw(const char *)
{

   if (this != &givenList)                // check that both lists are the same
   {
      try
      {
         Node <T> * pSource = givenList.pHead;        //Create a node to traverse list
         
         // allocate a new head
         Node <T> * pDestination = new Node <T> (pSource->data);
         Node <T> * pCurrent = pDestination;
         
 
         
         // loop through the rest of the source linked list
         while (pSource->pNext)
         {
            pSource = pSource->pNext;
            pCurrent->pNext = new Node <T> (pSource->data);
            pCurrent->pPrev = pSource->pPrev;
            pCurrent = pCurrent->pNext;
         }
         
         pCurrent->pPrev = pSource->pPrev;
         pTail = pCurrent;

         pHead = pDestination;
         

      }
      catch (bad_alloc)
      {
         throw "ERROR: unable to allocate a new node for a list";
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
   
   pTail = pHead;
   numElements = 0;
}


/*******************************************
 * List :: Push_back
 *  Adds a Node to the end of the list
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

/*******************************************
 * List :: Push_front
 *  Adds a node to the front of the list
 *******************************************/
template <class T>
void List <T> :: push_front(const T & t) throw (const char *)
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
void List <T> :: pop_front()
{
   Node <T> * pDelete = pHead;
   
   pHead = pHead->pNext;
   pHead->pPrev = NULL;
   pHead->pNext->pPrev = pHead;
   
   delete pDelete;
   numElements--;
   
   
}


/*******************************************
 * List :: Pop_back
 *  Remove a node from the end of the list
 *******************************************/
template <class T>
void List <T> :: pop_back()
{
   
   
   Node <T> * pDelete = pTail;
   
   pTail = pTail->pPrev;
   pTail->pNext = NULL;
   pTail->pPrev->pNext = pTail;
   
   delete pDelete;
   numElements--;
   
   
}


#endif /* list_h */
