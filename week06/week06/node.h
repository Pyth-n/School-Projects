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
   Node() : data(NULL), pNext(NULL), pPrev(NULL) {}
   Node(const T & t) :data(t), pNext(NULL), pPrev(NULL) {}
   
   friend ostream & operator << (std::ostream &out, Node <T> &rhs);
   
};

/***************************************************
 * operator<<
 * Display the contents of a given linked-list.
 
 **************************************************/
template <class T>
ostream & operator << (std::ostream &out, Node <T> &rhs)
{
   while (rhs)
   {
      out << rhs->data;
      rhs = rhs->next;
      
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
Node <T> * insert(Node <T> * pNode, const T & t, bool after = false)
{
   
/*   pNew NEW Node(e)
   IF pCurrent ≠ NULL and after = false
      pNew->pNext pCurrent
      pNew->pPrev pCurrent->pPrev
      pCurrent->pPrev pNew
   IF pNew->pPrev
      pNew->pPrev->pNext pNew
   
   IF pCurrent ≠ NULL and after = true
   ... something similar...
   
   
   RETURN pNew   */
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
  
  /* FOR p pHead ... p->next != NULL
   IF p data = e
      RETURN p

      RETURN NULL
   */

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

/***************************************************
 * freeData()
 * Release all the memory contained in a given linked-list. 
 * The one parameter is a pointer to the head of the list.

 **************************************************/
template <class T>
void freeData(Node <T> * & pHead)
{
   
   Node <T> * pNext;
   for (Node <T> * p = pHead; p; p = pNext)
   {
      
      //pDelete = pHead
      //pHead =  pHead->pNext
      //DELETE pDelete
      
   }
   pHead = NULL;
   
   
}

#endif /* node_h */
