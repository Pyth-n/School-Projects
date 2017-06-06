/***********************************************************************
 * Header:
 *    bnode.h
 * Summary:
 *    This will contain the code for our week08 Binary Tree assignment
 * Author
 *    Jeffry Simpson, David Perez
 ************************************************************************/

#ifndef bnode_h
#define bnode_h
#include <iostream>
using namespace std;

#include <cassert>


/************************************************
 * Node
 * Basic class Node
 ***********************************************/
template <class T>
class BinaryNode
{
public:
   // Member variables
   T data;
   BinaryNode <T> * pLeft, *pRight, *pParent;
   
   
   BinaryNode() : data(), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   BinaryNode(const T & t) : data(t), pLeft(NULL), pRight(NULL), pParent(NULL) {}
   
   friend int sizeBtree(BinaryNode <T> * pAdd);
   
   int size();
   void addLeft (BinaryNode <T> * pAdd);
   void addRight(BinaryNode <T> * pAdd);
   void addLeft (const T & t) throw (const char *);
   void addRight(const T & t) throw (const char *);
   
   //outstream insertion operator
   
};


template <class T>
void BinaryNode <T>::addLeft(const T & t) throw (const char *)
{
   BinaryNode <T> * pAdd = new BinaryNode <T>(t);
   pAdd->pParent = this;
   this->pLeft = pAdd;
   
}


template <class T>
BinaryNode <T> * copyBTree(const BinaryNode <T> * pSrc) throw (const char *)
{
   if (pSrc == NULL)
      return NULL;
   
   BinaryNode <T> * nDestination =  new BinaryNode <T>(pSrc->data);
   
   nDestination->pLeft =  copyBTree(pSrc->pLeft);
   
   if(nDestination->pLeft != NULL)
      nDestination->pLeft.pParent = nDestination;
      
      nDestination->pRight = copyBTree(pSrc->pRight);
      if(nDestination->pRight != NULL)
         nDestination->pRight.pParent = nDestination;
         
         return nDestination;
}


template <class T>
int BinaryNode <T>::size()
{
   
   if(NULL == this )
      return 0;
   else
      return (this->pLeft->size() + 1 + this->pRight->size());
}

template <class T>
void deleteBTree(BinaryNode <T> * & pNode)
{
   if(pNode == NULL)
      return;
   
   deleteBTree(pNode->pLeft);
   deleteBTree(pNode->pRight);
   delete pNode;
   
}





/*
 int sizeBTree(const BinaryNode <T> * node)
 {
 
 if(node == NULL)
 return 0;
 else
 return (sizeBTree(node->pLeft) + 1 + sizeBTree(node->pRight));
 }*/

#endif /* bnode_h */
