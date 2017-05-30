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
   List(const List<T> * rhs)    throw (const char *);
   ~List();
   
   
   //inLine functions
   bool empty() { return (!pHead && !pTail && (numElements== 0));}
   
   //Function definitions
   
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
      pTail - pHead;
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
List <T> ::List(const List<T> * pSource) throw (const char *)
{
   //Verify we got something to copy
   if (NULL != pSource)
   {

      try
      {
         // allocate a new head
         pHead = new Node <T> (pSource->data);
          numElements++;
         Node <T> * pCurrent = pHead;
        
         
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
         throw "ERROR: Can't allocate memory for a Node!";
      }
   }

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


#endif /* list_h */
