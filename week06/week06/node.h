/***********************************************************************
 * Header:
 *    set.h
 * Summary:
 *    This will contain the code for our week05 set assignment
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef node_h
#define node_h
#include <iostream>
using namespace std;

#include <cassert>



/************************************************
 * Node
 * Basic class for Linked List Node
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
   
   //friend ostream & operator << (std::ostream &out, Node <T> &rhs);
   
};

/***************************************************
 * operator<<
 * Display the contents of a given linked-list.
 
 **************************************************/
template <class T>
ostream & operator << (ostream & out, Node <T> * rhs)
{
   while (rhs)
   {
      out << rhs->data;
      if(rhs->pNext)
         out << ", ";
      rhs = rhs->pNext;

   }
   return out;
}

/***************************************************
 * copy()
 * Copy a linked-list. Takes a pointer to a Node as a parameter and returns a 
 * newly created linked-list containing a copy of all the nodes below the list 
 * represented by the parameter.
 **************************************************/
template <class T>
Node <T> * copy(const Node <T> * pSource) throw (const char *)
{
   // trivial case
   if (NULL == pSource)
      return NULL;
   
   try
   {
      // allocate a new head
      Node <T> * pDestination = new Node <T> (pSource->data);
      Node <T> * pCurrent = pDestination;
      
      // loop through the rest of the source linked list
      while (pSource->pNext)
      {
         pSource = pSource->pNext;
         pCurrent->pNext = new Node <T> (pSource->data);
         pCurrent = pCurrent->pNext;
      }
      
      return pDestination;
   }
   catch (bad_alloc)
   {
        throw "ERROR: Can't allocate memory for a Node!";
   }
   
}

/***************************************************
 * insert()
 * Insert a new Node into the current linked-list. The first parameter is the 
 *  value to be placed in the new Node. The second parameter is the Node preceding 
 *  the new Node in the list. An optional third parameter is set to true if 
 *  the new item is to be at the head of the list. Please return a pointer to 
 *  the newly created Node.
 **************************************************/
template <class T>
Node <T> * insert(const T & t, Node <T> * &pNode,  bool after = false)
{
   Node<T>* pNew = new Node<T>(t);

   
   // If it's empty
   if (NULL == pNode)
   {
      pNode = pNew;
      return pNew;

   }
   
   // Adds to back
   if (NULL != pNode && !after)
   {
      pNew->pNext = pNode->pNext;
      pNew->pPrev = pNode;
      pNode->pNext = pNew;
 
   }
   
   // Adds to head
   if (NULL != pNode && after)
   {
      pNew->pNext = pNode;
      pNode = pNew;
      return pNode;
   }

   return pNew;

}


/***************************************************
 * find()
 * Find the Node corresponding to a given passed value from a given linked-list. 
 *  The first parameter is a pointer to the front of the list, the second is the 
 *  value to be found. The return value is a pointer to the found node if one 
 *  exists.
 **************************************************/
template <class T>
Node <T> * find(Node <T> * pHead, const T & t)
{
   for (Node<T> *p = pHead; p; p = p->pNext)
   {
      if (p->data == t)
      {
         cout << "FOUND\n";
         return p;
      }
   }

   return NULL;
}

/***************************************************
 * freeData()
 * Release all the memory contained in a given linked-list. 
 * The one parameter is a pointer to the head of the list.
 **************************************************/
template <class T>
void freeData(Node <T> * & pHead)
{

   while (pHead != NULL)
   {
      Node <T> *pDelete = pHead;
      pHead = pHead->pNext;
      delete pDelete;
   }
}

/***************************************************
* Remove()
*  Delete a single node from a linked list
*
**************************************************/
//template <class T>
//Node <T> * remove(const Node <T> * pRemove)
//{

//}
#endif /* node_h */
